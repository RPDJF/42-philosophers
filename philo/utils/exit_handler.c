/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/30 00:34:59 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	destroy_philosophers(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		pthread_mutex_destroy(&((*philosophers)->fork));
		free(*philosophers);
		philosophers++;
	}
}

int	secure_exit(t_data *data)
{
	destroy_philosophers(data->philosophers);
	free(data->philosophers);
	free(data);
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
