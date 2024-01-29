/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/30 00:46:08 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_sleep(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->write_lock);
	printf("Philosopher %d is sleeping\n", philosopher->id);
	pthread_mutex_unlock(philosopher->write_lock);
	usleep(1000000 * *philosopher->time_to_sleep);
	philosopher->has_eaten = 0;
}

static void	philo_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->write_lock);
	printf("Philosopher %d is thinking\n", philosopher->id);
	pthread_mutex_unlock(philosopher->write_lock);
	pthread_mutex_lock(&philosopher->fork);
	pthread_mutex_lock(philosopher->r_fork);
	pthread_mutex_lock(philosopher->write_lock);
	printf("Philosopher %d has taken a fork\n", philosopher->id);
	pthread_mutex_unlock(philosopher->write_lock);
	usleep(1000000 * *philosopher->time_to_eat);
	philosopher->has_eaten = true;
	pthread_mutex_unlock(philosopher->r_fork);
	pthread_mutex_unlock(&philosopher->fork);
}

static void	*start_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	while (!check_death(philosopher))
	{
		if (!philosopher->has_eaten)
			philo_eat(philosopher);
		if (philosopher->has_eaten)
			philo_sleep(philosopher);
	}
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

	if (start_threads(data->philosophers) < 0)
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
		return (error_exit());
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	pthread_mutex_init(&data->write_lock, 0);
	pthread_mutex_init(&data->dead_lock, 0);
	if (start_philo(data) < 0)
		return (crash_exit());
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	return (secure_exit(data));
}
