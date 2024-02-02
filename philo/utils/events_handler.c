/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:39:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 18:34:04 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	check_death(t_philosopher *philosopher)
{
	bool	status;

	pthread_mutex_lock(philosopher->dead_lock);
	status = *philosopher->is_someone_dead;
	pthread_mutex_unlock(philosopher->dead_lock);
	return (status);
}

void	send_status(t_philosopher *philosopher, char *status)
{
	pthread_mutex_lock(philosopher->write_lock);
	if (*philosopher->is_someone_dead)
	{
		pthread_mutex_unlock(philosopher->write_lock);
		return ;
	}
	printf("%ld %d %s\n",
		get_difftimestamp(*philosopher->start_timeval),
		philosopher->id,
		status);
	pthread_mutex_unlock(philosopher->write_lock);
}
