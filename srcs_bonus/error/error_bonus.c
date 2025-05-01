/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaulas- <fpaulas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:43:13 by caubert           #+#    #+#             */
/*   Updated: 2025/04/18 11:06:42 by fpaulas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	error_msg(char *msg)
{
	printf("Error\n%s\n", msg);
	return (0);
}

int	error_msg_free(char *msg, void *ptr)
{
	printf("Error\n%s\n", msg);
	if (ptr)
		free(ptr);
	return (0);
}
