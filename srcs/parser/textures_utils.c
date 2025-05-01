/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:03:09 by caubert           #+#    #+#             */
/*   Updated: 2025/02/18 16:03:09 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_texture_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (error_msg("Texture file needs .xpm extension"));
	if (ft_strcmp(path + len - 4, ".xpm") != 0)
		return (error_msg("Texture file must be .xpm"));
	return (1);
}

int	validate_texture_identifier(char *line, int *i)
{
	while (line && ft_isspace(line[0]))
		line++;
	if (!line || !line[0] || !line[1])
		return (error_msg("Invalid texture identifier"));
	if ((line[0] != 'N' || line[1] != 'O') && \
		(line[0] != 'S' || line[1] != 'O') && \
		(line[0] != 'W' || line[1] != 'E') && \
		(line[0] != 'E' || line[1] != 'A'))
		return (error_msg("Unknown texture identifier"));
	*i = 2;
	if (!line[*i])
		return (error_msg("Missing texture path"));
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (error_msg("Missing texture path after identifier"));
	return (1);
}

char	*extract_texture_path(char *line, int start)
{
	char	*path;
	char	*tmp;

	tmp = ft_strtrim(line + start, " \t\n\r\v\f");
	if (!tmp || !*tmp)
	{
		free(tmp);
		return (NULL);
	}
	path = ft_strdup(tmp);
	free(tmp);
	return (path);
}
