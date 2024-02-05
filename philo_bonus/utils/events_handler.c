/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:39:58 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/05 17:22:33 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	check_death(t_philosopher *philosopher)
{
	bool	status;

	sem_wait(*philosopher->dead_lock);
	status = *philosopher->is_someone_dead;
	sem_post(*philosopher->dead_lock);
	return (status);
}

void	send_status(t_philosopher *philosopher, char *status)
{
	sem_wait(*philosopher->write_lock);
	if (*philosopher->is_someone_dead)
	{
		sem_post(*philosopher->write_lock);
		return ;
	}
	printf("%ld %d %s\n",
		get_difftimestamp(*philosopher->start_timeval),
		philosopher->id,
		status);
	sem_post(*philosopher->write_lock);
}
