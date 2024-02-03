/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:54:53 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	start_threads(t_data *data)
{
	pthread_t		thread_checker;
	t_philosopher	**philosophers;

	philosophers = data->philosophers;
	while (*philosophers)
	{
		if (pthread_create(&(*philosophers)->thread, 0,
				philosopher_routine, *philosophers))
			return (-1);
		philosophers++;
	}
	pthread_create(&thread_checker, 0, hypervisor_routine, data);
	pthread_join(thread_checker, 0);
	return (0);
}

static int	start_philo(t_data *data)
{
	t_philosopher	**philosophers;

	if (start_threads(data) < 0)
		return (-1);
	philosophers = data->philosophers;
	while (*philosophers)
		pthread_join((*(philosophers++))->thread, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (error_exit("Wrong usage."));
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	gettimeofday(&data->start_timeval, 0);
	pthread_mutex_init(&data->write_lock, 0);
	pthread_mutex_init(&data->dead_lock, 0);
	if (start_philo(data) < 0)
		return (crash_exit());
	return (secure_exit());
}
