/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:09:35 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 18:35:03 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	init_forks(t_data *data, t_philosopher *philosopher, int id)
{
	pthread_mutex_init(&philosopher->fork, 0);
	if (id - 1 > 0)
	{
		philosopher->l_fork = &data->philosophers[id - 2]->fork;
		data->philosophers[id - 2]->r_fork = &philosopher->fork;
	}
	else
		philosopher->l_fork = &philosopher->fork;
	if (id != 1 && id == data->number_of_philosophers)
	{
		data->philosophers[0]->l_fork = &philosopher->fork;
		philosopher->r_fork = &data->philosophers[0]->fork;
	}
	else if (id == 1 && id == data->number_of_philosophers)
		philosopher->r_fork = &philosopher->fork;
}

int	init_philosophers(t_data *data)
{
	int	idx;

	idx = -1;
	while (idx++, idx < data->number_of_philosophers)
	{
		data->philosophers = ft_reallocf(data->philosophers,
				(size_t)idx * sizeof(t_philosopher **),
				((size_t)idx + 1) * sizeof(t_philosopher **));
		if (!data->philosophers)
			return (-1);
		data->philosophers[idx] = new_philosopher(data);
		if (!data->philosophers[idx])
			return (-1);
	}
	data->philosophers = ft_reallocf(data->philosophers,
			(size_t)idx * sizeof(t_philosopher **),
			((size_t)idx + 1) * sizeof(t_philosopher **));
	if (!data->philosophers)
		return (-1);
	data->philosophers[idx] = 0;
	return (0);
}
