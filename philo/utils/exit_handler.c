/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:26:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/05 19:48:47 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	destroy_mutex(t_data *data)
{
	t_philosopher	**philosophers;

	philosophers = data->philosophers;
	while (*philosophers)
		pthread_mutex_destroy(&(*(philosophers++))->fork);
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_unlock(&data->write_lock);
	pthread_mutex_destroy(&data->write_lock);
}

int	secure_exit(t_data *data)
{
	destroy_data(data);
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
