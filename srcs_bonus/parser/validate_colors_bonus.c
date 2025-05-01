/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_colors_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:39:23 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:07:40 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	validate_color_split(char **split)
{
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		return (error_msg("Invalid color format"));
	}
	return (1);
}

static int	validate_color_format(char *line, char *trimmed)
{
	if (!check_initial_comma(line + 1) || check_trailing_comma(trimmed) || \
		check_consecutive_commas(trimmed))
	{
		free(trimmed);
		return (error_msg("Invalid color format"));
	}
	return (1);
}

static int	process_color_value(char *str, int *color_value)
{
	char	*tmp;
	int		value;

	tmp = ft_strtrim(str, " \t\n\r\v\f");
	if (!tmp)
		return (error_msg("Memory allocation failed"));
	if (!is_valid_number(tmp))
	{
		free(tmp);
		return (error_msg("Invalid color number"));
	}
	value = ft_atoi(tmp);
	free(tmp);
	*color_value = value;
	return (1);
}

static int	parse_color_values(char **split, int *color)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!process_color_value(split[i], &color[i]))
		{
			free_split(split);
			return (0);
		}
	}
	return (1);
}

/*Parses color scheme ensuring it respects the correct R,G,B pattern.*/
int	parse_color(char *line, int *color)
{
	char	**split;
	char	*trimmed;
	char	*identifier;

	if (color[0] != -1)
		return (error_msg("Duplicate color definition"));
	identifier = line;
	while (*identifier && ft_isspace(*identifier))
		identifier++;
	trimmed = ft_strtrim(identifier + 1, " \t\n\r\v\f");
	if (!trimmed)
		return (0);
	if (!validate_color_format(line, trimmed))
		return (0);
	split = ft_split(trimmed, ',');
	free(trimmed);
	if (!validate_color_split(split))
		return (0);
	if (!parse_color_values(split, color))
		return (0);
	free_split(split);
	return (1);
}

/*
int	parse_color(char *line, int *color)
{
	char	**split;
	char	*trimmed;
	char	*identifier;
	int		i;
	int		value;
	char	*tmp;

	if (color[0] != -1)
		return (error_msg("Duplicate color definition"));
	identifier = line;
	while (*identifier && ft_isspace(*identifier))
		identifier++;
	trimmed = ft_strtrim(identifier + 1, " \t\n\r\v\f");
	if (!trimmed)
		return (0);
	if (!check_initial_comma(line + 1) || check_trailing_comma(trimmed) || \
			check_consecutive_commas(trimmed))
	{
		free(trimmed);
		return (error_msg("Invalid color format"));
	}
	split = ft_split(trimmed, ',');
	free(trimmed);
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		free_split(split);
		return (error_msg("Invalid color format"));
	}
	i = -1;
	while (++i < 3)
	{
		tmp = ft_strtrim(split[i], " \t\n\r\v\f");
		if (!tmp)
		{
			free_split(split);
			return (error_msg("Memory allocation failed"));
		}
		if (!is_valid_number(tmp))
		{
			free(tmp);
			free_split(split);
			return (error_msg("Invalid color number"));
		}
		value = ft_atoi(tmp);
		free(tmp);
		color[i] = value;
	}
	free_split(split);
	return (1);
}
*/
