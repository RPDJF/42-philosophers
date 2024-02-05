/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hypervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:54:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/05 19:07:40 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*static int	check_finish(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		if ((*philosophers)->eat_counter >= *(*philosophers)->max_eat_counter)
			return (0);
		philosophers++;
	}
	return (1);
}*/

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

void	hypervisor(t_data *data)
{
	sem_wait(data->living_philos);
	kill_philosophers(data);
	sem_post(data->living_philos);
}
