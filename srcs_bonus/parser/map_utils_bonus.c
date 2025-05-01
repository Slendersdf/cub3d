/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:28:48 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:16 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	check_valid_chars(char c)
{
	return (c == '0' || c == '1' || c == 'N' || \
			c == 'S' || c == 'E' || c == 'W' || \
			c == 'D' || c == ' ');
}

int	is_map_line(char *line)
{
	int	i;

	if (is_empty_or_spaces(line))
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	return (line[i] == '0' || line[i] == '1' || line[i] == 'N' || \
			line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || \
			line[i] == ' ');
}

int	is_empty_or_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_line(char *line)
{
	size_t	len;
	size_t	last_char;

	len = ft_strlen(line);
	last_char = len;
	while (last_char > 0 && ft_isspace(line[last_char - 1]))
		last_char--;
	while (*line && ft_isspace(*line))
		line++;
	if (*line == '\0' || last_char == 0)
		return (0);
	return (1);
}

int	check_trailing_chars(char *line)
{
	int	i;
	int	last_char;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (0);
	last_char = i;
	while (line[last_char + 1])
		last_char++;
	while (last_char > i && ft_isspace(line[last_char]))
		last_char--;
	while (i <= last_char)
	{
		if (!check_valid_chars(line[i]))
			return (0);
		i++;
	}
	return (1);
}
