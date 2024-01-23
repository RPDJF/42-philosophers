/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:28:11 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	secure_exit(void)
{
	cleargarbage();
	return (0);
}

int	error_exit(void)
{
	cleargarbage();
	return (1);
}

int	crash_exit(void)
{
	cleargarbage();
	ft_putendl_fd("Error", 2);
	return (1);
}
