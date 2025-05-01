/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_line_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:09:51 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:01 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	calculate_line_length(char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	return (len);
}

static void	handle_tab_spaces(char *new_line, int *j)
{
	int	spaces;

	spaces = 4;
	while (spaces--)
	{
		new_line[*j] = ' ';
		(*j)++;
	}
}

static int	handle_regular_char(char *new_line, char c, int *j)
{
	if (ft_isspace(c))
		new_line[*j] = ' ';
	else if (!check_valid_chars(c))
	{
		free(new_line);
		return (0);
	}
	else
		new_line[*j] = c;
	(*j)++;
	return (1);
}

char	*dup_line_with_spaces(char *line)
{
	char	*new_line;
	int		len;
	int		i;
	int		j;

	len = calculate_line_length(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			handle_tab_spaces(new_line, &j);
		else if (!handle_regular_char(new_line, line[i], &j))
			return (NULL);
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

/*
char	*dup_line_with_spaces(char *line)
{
	char	*new_line;
	int		len;
	int		i;
	int		j;
	int		spaces;

	len = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			spaces = 4;
			while (spaces--)
			{
				new_line[j] = ' ';
				j++;
			}
		}
		else
		{
			if (ft_isspace(line[i]))
				new_line[j] = ' ';
			else if (!check_valid_chars(line[i]))
			{
				free(new_line);
				return (NULL);
			}
			else
				new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
*/
