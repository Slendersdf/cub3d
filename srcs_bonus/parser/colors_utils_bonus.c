/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:17:04 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:06:52 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	check_initial_comma(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == ',')
		return (0);
	return (1);
}

int	check_trailing_comma(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
		len--;
	if (len > 0 && str[len - 1] == ',')
		return (1);
	return (0);
}

int	check_consecutive_commas(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	int		i;
	int		value;
	char	*temp;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	value = 0;
	temp = str + i;
	i = 0;
	while (temp[i])
	{
		if (!ft_isdigit(temp[i]) && !ft_isspace(temp[i]))
			return (0);
		if (ft_isdigit(temp[i]))
		{
			value = (value * 10) + (temp[i] - '0');
			if (value > 255)
				return (0);
		}
		i++;
	}
	return (1);
}
