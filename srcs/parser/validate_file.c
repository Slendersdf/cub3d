/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:13:30 by caubert           #+#    #+#             */
/*   Updated: 2025/02/08 13:13:30 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*get_basename(char *filename)
{
	char	*basename;
	int		len;

	if (!filename)
		return (NULL);
	len = ft_strlen(filename);
	if (len > 0 && filename[len - 1] == '/')
		return (NULL);
	basename = ft_strrchr(filename, '/');
	if (basename)
		return (basename + 1);
	return (filename);
}

/*
 * This function opens the fd in order to read from the map file. That's it.
*/
static int	open_file(char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	read_ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error_msg("No such file or directory");
		return (-1);
	}
	read_ret = read(fd, buffer, 1);
	if (read_ret < 0)
	{
		close(fd);
		error_msg("Is a directory");
		return (-1);
	}
	if (read_ret == 0)
	{
		close(fd);
		error_msg("Permission denied or empty file");
		return (-1);
	}
	return (fd);
}

/*
 * Pretty straightforward function, searching in the file name what is after
 * the dot extension. If it differs from .cub, whether because the filename
 * is shorter than 4 digits or because its only name is ".cub", it returns
 * an error, if not, it simply continues.
 * ext = extension
*/
static int	check_extension(char *basename)
{
	size_t	len;
	int		dot_count;
	int		i;

	if (!basename || basename[0] == '.')
		return (0);
	len = ft_strlen(basename);
	if (len <= 4)
		return (0);
	dot_count = 0;
	i = 0;
	while (basename[i])
	{
		if (basename[i] == '.')
			dot_count++;
		i++;
	}
	if (dot_count != 1)
		return (0);
	if (ft_strcmp(basename + len - 4, ".cub") != 0)
		return (0);
	if (len == 4)
		return (0);
	return (1);
}

/*
 * Main file validation function. It checks if the extension has the correct
 * type before trying to open the map file. It returns an error in case of
 * any unattended problem.
*/
int	validate_file(char *filename)
{
	char	*basename;
	int		fd;

	if (!filename)
		return (error_msg("No filename provided"));
	basename = get_basename(filename);
	if (!check_extension(basename))
		return (error_msg("Invalid file extension"));
	fd = open_file(filename);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}
