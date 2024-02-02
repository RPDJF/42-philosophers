/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:08:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 09:37:19 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

long	get_timestamp(struct timeval time)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((end.tv_sec - time.tv_sec) * 1000
		+ (end.tv_usec - time.tv_usec) / 1000);
}

void	mssleep(long time_in_ms)
{
	long int		time;
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	time = get_timestamp(timestamp);
	while (get_timestamp(timestamp) - time < time_in_ms)
		usleep(time_in_ms / 10);
}
