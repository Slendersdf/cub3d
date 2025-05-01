/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:09:51 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 11:09:51 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Counts the total length of the line, considering tabs as 4 spaces. */
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

/* Handles a tab character by replacing it with 4 spaces. */
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

/* Handles regular characters, converting spaces and validating map chars. */
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

/* Creates a new line with tabs converted to spaces and validates characters. */
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
