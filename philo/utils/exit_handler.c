/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 20:47:21 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"


// planning garbage collector

int	secure_exit(void)
{
	return (0);
}

int	error_exit(void)
{
	return (1);
}

int	crash_exit(void)
{
	printf("Error\n");
	return (1);
}
