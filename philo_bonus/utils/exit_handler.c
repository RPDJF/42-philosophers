/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 16:19:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	unlink_sems(void)
{
	sem_unlink("FORKS_LOCKER");
	sem_unlink("WRITE_LOCK");
	sem_unlink("DEAD_LOCK");
	sem_unlink("LIVING_LOCKER");
}

int	secure_exit(void)
{
	unlink_sems();
	exit(0);
}

int	error_exit(char *error)
{
	unlink_sems();
	printf("%s\n", error);
	exit(1);
}

int	crash_exit(void)
{
	unlink_sems();
	printf("Error\n");
	exit(1);
}
