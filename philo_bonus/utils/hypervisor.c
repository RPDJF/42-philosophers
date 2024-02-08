/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:54:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 11:17:44 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	check_finish(t_philosopher *philosopher)
{
	if (!*philosopher->max_eat_counter)
		return (0);
	if (philosopher->eat_counter >= *philosopher->max_eat_counter)
		return (1);
	return (0);
}

int	check_starving(t_philosopher *philosopher)
{
	long	timestamp;

	if (*philosopher->max_eat_counter
		&& philosopher->eat_counter >= *philosopher->max_eat_counter)
		return (0);
	timestamp = get_difftimestamp(philosopher->last_time_eating);
	if (timestamp >= *philosopher->time_to_die)
		return (1);
	return (0);
}

static void	kill_philosophers(t_data *data)
{
	t_philosopher	**philosophers;

	sem_wait(data->dead_lock);
	data->is_dead = true;
	philosophers = data->philosophers;
	while (*philosophers)
		kill((*(philosophers++))->pid, SIGKILL);
	sem_post(data->dead_lock);
}

void	*hypervisor(void *param)
{
	t_data	*data;

	data = param;
	sem_wait(data->living_philos);
	kill_philosophers(data);
	sem_post(data->living_philos);
	return (0);
}
