/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:48:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 09:58:15 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	philo_sleep(t_philosopher *philosopher)
{
	send_status(philosopher, "is sleeping");
	if (!check_death(philosopher))
		mssleep(*philosopher->time_to_sleep);
	philosopher->has_eaten = 0;
	philosopher->has_think = 0;
}

static void	philo_think(t_philosopher *philosopher)
{
	send_status(philosopher, "is thinking");
	philosopher->has_think = true;
}

static void	philo_eat(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->r_fork);
	send_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->fork);
	send_status(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->eat_lock);
	send_status(philosopher, "is eating");
	if (!check_death(philosopher))
	{
		mssleep(*philosopher->time_to_eat);
		philosopher->has_eaten = true;
		gettimeofday(&philosopher->last_time_eating, 0);
	}
	pthread_mutex_unlock(&philosopher->eat_lock);
	pthread_mutex_unlock(&philosopher->fork);
	pthread_mutex_unlock(philosopher->r_fork);
}

void	*philosopher_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	while (true)
	{
		if (check_death(philosopher))
			break ;
		if (!philosopher->has_think)
			philo_think(philosopher);
		else if (!philosopher->has_eaten)
			philo_eat(philosopher);
		else
			philo_sleep(philosopher);
	}
	return (0);
}
