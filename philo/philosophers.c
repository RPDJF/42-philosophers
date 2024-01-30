/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/31 00:06:47 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_starving(t_philosopher *philosopher)
{
	long	timestamp;

	timestamp = get_timestamp(philosopher->last_time_eating);
	if (timestamp >= *philosopher->time_to_die)
	{
		pthread_mutex_lock(&philosopher->eat_lock);
		send_status(philosopher, "died");
		pthread_mutex_unlock(&philosopher->eat_lock);
		return (1);
	}
	return (0);
}

static void	philo_sleep(t_philosopher *philosopher)
{
	send_status(philosopher, "is sleeping");
	if (!check_death(philosopher))
		mssleep(*philosopher->time_to_sleep);
	philosopher->has_eaten = 0;
}

static void	philo_eat(t_philosopher *philosopher)
{
	send_status(philosopher, "is thinking");
	pthread_mutex_lock(philosopher->r_fork);
	send_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->fork);
	send_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->eat_lock);
	send_status(philosopher, "is eating");
	if (!check_death(philosopher))
	{
		mssleep(*philosopher->time_to_eat);
		philosopher->has_eaten = true;
		gettimeofday(&philosopher->last_time_eating, 0);
	}
	pthread_mutex_unlock(&philosopher->eat_lock);
	pthread_mutex_unlock(&philosopher->fork);
	pthread_mutex_unlock(philosopher->r_fork);
}

static void	*start_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	while (true)
	{
		if (check_death(philosopher))
			break ;
		philo_eat(philosopher);
		if (check_death(philosopher))
			break ;
		philo_sleep(philosopher);
	}
	return (0);
}

static void	*hypervisor_routine(void *param)
{
	t_data	*data;
	int		i;
	int		j;

	data = (t_data *)param;
	while (true)
	{
		i = -1;
		while (i++, data->philosophers[i])
		{
			if (check_death(data->philosophers[i]))
				return (0);
			if (check_starving(data->philosophers[i]))
			{
				pthread_mutex_lock(&data->dead_lock);
				data->is_dead = true;
				j = -1;
				while (data->philosophers[++j])
					pthread_mutex_unlock(&data->philosophers[j]->fork);
				pthread_mutex_unlock(&data->dead_lock);
			}
		}
		usleep(5000);
	}
	return (0);
}

static int	start_threads(t_data *data)
{
	pthread_t		thread_checker;
	t_philosopher	**philosophers;

	philosophers = data->philosophers;
	while (*philosophers)
	{
		if (pthread_create(&(*philosophers)->thread, 0,
				start_routine, *philosophers))
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
		return (error_exit());
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit(0));
	gettimeofday(&data->start_timeval, 0);
	pthread_mutex_init(&data->write_lock, 0);
	pthread_mutex_init(&data->dead_lock, 0);
	if (start_philo(data) < 0)
		return (crash_exit(data));
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	return (secure_exit(data));
}
