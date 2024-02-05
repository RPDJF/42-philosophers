/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:09:35 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/05 18:28:13 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

sem_t	*init_forks(int nb_forks)
{
	static sem_t	*forks;

	if (!forks)
		forks = sem_open("FORKS_LOCKER", O_CREAT | O_EXCL, 0600, nb_forks);
	return (forks);
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
