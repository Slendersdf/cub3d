/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:16:54 by caubert           #+#    #+#             */
/*   Updated: 2025/02/08 16:16:54 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	handle_texture_error(int fd)
{
	if (fd != -1)
		close(fd);
	if (errno == EISDIR)
		return (error_msg("Texture path is a directory"));
	if (errno == EACCES)
		return (error_msg("Permission denied for texture file"));
	return (error_msg("Cannot open texture file"));
}

static int	check_texture_path(char *path)
{
	int		fd;
	char	buffer[1];
	ssize_t	read_ret;

	if (!check_texture_extension(path))
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (handle_texture_error(-1));
	read_ret = read(fd, buffer, 1);
	if (read_ret < 0)
		return (handle_texture_error(fd));
	if (read_ret == 0)
	{
		close(fd);
		return (error_msg("Texture file is empty"));
	}
	close(fd);
	return (1);
}

/*Parses a texture line, ensuring there's no errors in it, such as path, empty
 * file and so on using the 2 utilitaries above.*/
int	parse_texture(char *line, char **texture)
{
	char	*path;
	int		i;
	char	*trimmed;

	if (*texture)
		return (error_msg("Duplicate texture definition"));
	trimmed = line;
	while (trimmed && ft_isspace(*trimmed))
		trimmed++;
	if (!validate_texture_identifier(trimmed, &i))
		return (0);
	path = extract_texture_path(trimmed, i);
	if (!path)
		return (error_msg("Empty texture path"));
	if (!check_texture_path(path))
	{
		free(path);
		return (0);
	}
	*texture = path;
	return (1);
}
