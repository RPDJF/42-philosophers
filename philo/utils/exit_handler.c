/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 18:36:42 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_data	*destroy_data(t_data *data)
{
	t_philosopher	**philosopher;

	philosopher = data->philosophers;
	if (philosopher)
	{
		while (*philosopher)
		{
			pthread_mutex_unlock(&((*philosophers)->fork));
			pthread_mutex_destroy(&((*philosophers)->fork));
			pthread_mutex_unlock(&((*philosophers)->eat_lock));
			pthread_mutex_destroy(&((*philosophers)->eat_lock));
			free(*philosopher);
			philosopher++;
		}
	}
	free(data->philosophers);
	free(data);
	return (0);
}

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
