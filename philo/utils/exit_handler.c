/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:56:09 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	secure_exit(void)
{
	cleargarbage();
	return (0);
}

int	error_exit(char *error)
{
	printf("%s\n", error);
	cleargarbage();
	return (1);
}

int	crash_exit(void)
{
	printf("Error\n");
	cleargarbage();
	return (1);
}
