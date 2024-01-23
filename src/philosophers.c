/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 06:25:48 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	mutex;

static void	*start_routine(void *param)
{
	t_philosopher	*philosopher;

	pthread_mutex_lock(&mutex);
	philosopher = (t_philosopher *)param;
	ft_printf("Je suis le %dième philosopher !\n", philosopher->id);
	pthread_mutex_unlock(&mutex);
	return (0);
}

static int	start_threads(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		if (pthread_create(&(*philosophers)->thread, NULL, start_routine, *philosophers))
			return (-1);
		philosophers++;
	}
	return (0);
}

static int	start_philo(t_data *data)
{
	t_philosopher	**philosophers;

	pthread_mutex_init(&mutex, 0);
	if (start_threads(data->philosophers) < 0)
		return (-1);
	philosophers = data->philosophers;
	while (*philosophers)
		pthread_join((*(philosophers++))->thread, 0);
	pthread_mutex_destroy(&mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (error_exit());
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	if (start_philo(data) < 0)
		return (crash_exit());
	return (secure_exit());
}
