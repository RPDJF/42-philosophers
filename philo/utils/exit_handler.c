/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/31 02:32:39 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	destroy_philosophers(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		pthread_mutex_unlock(&((*philosophers)->fork));
		pthread_mutex_destroy(&((*philosophers)->fork));
		pthread_mutex_unlock(&((*philosophers)->eat_lock));
		pthread_mutex_destroy(&((*philosophers)->eat_lock));
		free(*philosophers);
		philosophers++;
	}
}

int	secure_exit(t_data *data)
{
	destroy_philosophers(data->philosophers);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->philosophers);
	free(data);
	return (0);
}

int	error_exit(void)
{
	return (1);
}

int	crash_exit(t_data *data)
{
	printf("Error\n");
	if (data)
	{
		destroy_philosophers(data->philosophers);
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->write_lock);
		free(data->philosophers);
		free(data);
	}
	return (1);
}
