/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 03:48:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 11:05:16 by rude-jes         ###   ########.fr       */
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
	sem_wait(philosopher->forks);
	send_status(philosopher, "has taken a fork");
	sem_wait(philosopher->forks);
	send_status(philosopher, "has taken a fork");
	send_status(philosopher, "is eating");
	if (!check_death(philosopher))
	{
		mssleep(*philosopher->time_to_eat);
		philosopher->has_eaten = true;
		gettimeofday(&philosopher->last_time_eating, 0);
	}
	philosopher->eat_counter++;
	sem_post(philosopher->forks);
	sem_post(philosopher->forks);
}

void	*philosopher_reaper(void *param)
{
	t_philosopher	*philosopher;

	philosopher = param;
	while (true)
	{
		sem_wait(*philosopher->dead_lock);
		if (check_finish(philosopher))
		{
			sem_post(*philosopher->living_philos);
			sem_post(*philosopher->dead_lock);
			exit(0);
		}
		else if (check_starving(philosopher))
		{
			sem_post(*philosopher->living_philos);
			sem_post(*philosopher->dead_lock);
			send_status(philosopher, "is dead");
			exit(0);
		}
		sem_post(*philosopher->dead_lock);
		mssleep(2);
	}
}

void	*philosopher_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	pthread_create(&philosopher->reaper_thread, 0, philosopher_reaper, param);
	while (true)
	{
		if (*philosopher->max_eat_counter
			&& philosopher->eat_counter >= *philosopher->max_eat_counter)
			break ;
		if (philosopher->wait)
		{
			mssleep(5);
			philosopher->wait = false;
		}
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
