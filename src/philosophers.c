/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/29 18:28:30 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	display(t_philosopher *philosopher, char *s)
{
	char	*tmp;

	pthread_mutex_lock(philosopher->write_lock);
	tmp = ft_itoa(philosopher->id);
	if (!tmp)
		return (-1);
	tmp = ft_strreplace(s, "{id}", tmp);
	if (!tmp)
		return (-1);
	ft_putendl_fd(tmp, STDOUT_FILENO);
	gfree(tmp);
	pthread_mutex_unlock(philosopher->write_lock);
	return (0);
}

static void	*start_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	pthread_mutex_lock(&philosopher->fork);
	pthread_mutex_lock(philosopher->r_fork);
	display(philosopher, "Philosopher {id} is eating.");
	usleep(1000000 * *philosopher->time_to_eat);
	display(philosopher, "Philosopher {id} finished eating.");
	pthread_mutex_unlock(philosopher->r_fork);
	pthread_mutex_unlock(&philosopher->fork);
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
	if (start_philo(data) < 0)
		return (crash_exit());
	return (secure_exit());
}
