/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:39:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/29 21:55:41 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	update_death(t_philosopher *philosopher, bool status)
{
	pthread_mutex_lock(philosopher->dead_lock);
	*philosopher->is_someone_dead = status;
	pthread_mutex_unlock(philosopher->dead_lock);
}

bool	check_death(t_philosopher *philosopher)
{
	bool	status;

	pthread_mutex_lock(philosopher->dead_lock);
	status = *philosopher->is_someone_dead;
	pthread_mutex_unlock(philosopher->dead_lock);
	return (status);
}
