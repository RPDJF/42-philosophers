/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:54:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 16:23:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	check_philosopher_done(t_philosopher *philosopher)
{
	if (!*philosopher->max_eat_counter)
		return (0);
	pthread_mutex_lock(&philosopher->eat_lock);
	if (philosopher->eat_counter < *philosopher->max_eat_counter)
	{
		pthread_mutex_unlock(&philosopher->eat_lock);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->eat_lock);
	return (1);
}

static int	check_finish(t_philosopher **philosophers)
{
	if (!*(*philosophers)->max_eat_counter)
		return (0);
	while (*philosophers)
		if (!check_philosopher_done(*(philosophers++)))
			return (0);
	return (1);
}

static int	check_starving(t_philosopher *philosopher)
{
	long	timestamp;

	pthread_mutex_lock(&philosopher->eat_lock);
	if (*philosopher->max_eat_counter
		&& philosopher->eat_counter >= *philosopher->max_eat_counter)
	{
		pthread_mutex_unlock(&philosopher->eat_lock);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->eat_lock);
	timestamp = get_difftimestamp(philosopher->last_time_eating);
	if (timestamp >= *philosopher->time_to_die)
		return (1);
	return (0);
}

static void	kill_philosopher(t_data *data, t_philosopher *philosopher)
{
	int		j;

	pthread_mutex_lock(&data->dead_lock);
	data->is_dead = true;
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d died\n",
		get_difftimestamp(data->start_timeval),
		philosopher->id);
	pthread_mutex_unlock(&data->write_lock);
	pthread_mutex_unlock(&data->dead_lock);
	j = -1;
	while (j++, data->philosophers[j])
		pthread_mutex_unlock(&data->philosophers[j]->fork);
}

void	*hypervisor_routine(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	while (true)
	{
		if (check_finish(data->philosophers))
			break ;
		i = -1;
		while (i++, data->philosophers[i])
		{
			if (check_death(data->philosophers[i]))
				return (0);
			if (!check_philosopher_done(data->philosophers[i])
				&& check_starving(data->philosophers[i]))
				kill_philosopher(data, data->philosophers [i]);
		}
		mssleep(1);
	}
	return (0);
}
