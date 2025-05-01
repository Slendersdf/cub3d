/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caubert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:43:13 by caubert           #+#    #+#             */
/*   Updated: 2025/02/08 19:43:13 by caubert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Prins a specified error message depending on the circumstances. */
int	error_msg(char *msg)
{
	printf("Error\n%s\n", msg);
	return (0);
}

/* Frees the designated ptr in case of a special error msg. */
int	error_msg_free(char *msg, void *ptr)
{
	printf("Error\n%s\n", msg);
	if (ptr)
		free(ptr);
	return (0);
}
