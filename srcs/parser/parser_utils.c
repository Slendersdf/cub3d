/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:39:38 by caubert           #+#    #+#             */
/*   Updated: 2025/02/19 09:39:38 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	get_line_type(char *line)
{
	char	*trimmed;

	if (!line)
		return (-1);
	if (is_empty_line(line))
		return (0);
	trimmed = line;
	while (*trimmed && ft_isspace(*trimmed))
		trimmed++;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (2);
	if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (3);
	if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (4);
	if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (5);
	if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (6);
	if (ft_strchr("01NSEW", trimmed[0]))
		return (7);
	return (-1);
}

int	check_all_elements_loaded(t_map *map)
{
	if (!map->textures.no)
		return (error_msg("North texture missing"));
	if (!map->textures.so)
		return (error_msg("South texture missing"));
	if (!map->textures.we)
		return (error_msg("West texture missing"));
	if (!map->textures.ea)
		return (error_msg("East texture missing"));
	if (map->textures.f[0] == -1)
		return (error_msg("Floor color missing"));
	if (map->textures.c[0] == -1)
		return (error_msg("Ceiling color missing"));
	return (1);
}
