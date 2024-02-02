/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:54:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 10:03:45 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	check_starving(t_philosopher *philosopher)
{
	long	timestamp;

	pthread_mutex_lock(&philosopher->eat_lock);
	timestamp = get_difftimestamp(philosopher->last_time_eating);
	if (timestamp > *philosopher->time_to_die)
	{
		pthread_mutex_unlock(&philosopher->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->eat_lock);
	return (0);
}

static void	kill_philosopher(t_data *data, t_philosopher *philosopher)
{
	pthread_mutex_lock(&data->dead_lock);
	data->is_dead = true;
	pthread_mutex_lock(&data->write_lock);
	printf("%ld %d died\n",
		get_difftimestamp(data->start_timeval),
		philosopher->id);
	pthread_mutex_unlock(&data->write_lock);
	pthread_mutex_unlock(&data->dead_lock);
}

void	*hypervisor_routine(void *param)
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
				kill_philosopher(data, data->philosophers[i]);
				j = -1;
				while (j++, data->philosophers[j])
					pthread_mutex_unlock(&data->philosophers[j]->fork);
			}
		}
		mssleep(5);
	}
	return (0);
}
