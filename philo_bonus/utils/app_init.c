/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:53:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 12:37:38 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_void_satus(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
		philosopher->wait = false;
	else
		philosopher->wait = true;
}

t_philosopher	*new_philosopher(t_data *data)
{
	t_philosopher	*philosopher;
	static int		id;

	philosopher = galloc(sizeof(t_philosopher));
	if (!philosopher)
		return (0);
	philosopher->id = ++id;
	init_void_satus(philosopher);
	philosopher->eat_counter = 0;
	philosopher->max_eat_counter
		= &data->number_of_times_each_philosopher_must_eat;
	philosopher->write_lock = &data->write_lock;
	philosopher->has_think = false;
	gettimeofday(&philosopher->last_time_eating, NULL);
	philosopher->start_timeval = &data->start_timeval;
	philosopher->forks = init_forks(data->number_of_philosophers);
	philosopher->living_philos = &data->living_philos;
	philosopher->is_someone_dead = &data->is_dead;
	philosopher->dead_lock = &data->dead_lock;
	philosopher->time_to_die = &data->time_to_die;
	philosopher->time_to_eat = &data->time_to_eat;
	philosopher->time_to_sleep = &data->time_to_sleep;
	return (philosopher);
}

// need to protect philosopherS creation

t_data	*app_init(int argc, char **argv)
{
	t_data	*data;

	data = galloc(sizeof(t_data));
	if (!data)
		return (0);
	data->is_dead = false;
	data->philosophers = 0;
	data->number_of_philosophers = parse_pint(argv[1]);
	if (data->number_of_philosophers < 0)
		return (0);
	data->time_to_die = parse_pint(argv[2]);
	if (data->time_to_die < 0)
		return (0);
	data->time_to_eat = parse_pint(argv[3]);
	if (data->time_to_eat < 0)
		return (0);
	data->time_to_sleep = parse_pint(argv[4]);
	if (data->time_to_sleep < 0)
		return (0);
	if (init_simulation_limit(data, argc, argv) < 0)
		return (0);
	if (init_philosophers(data) < 0)
		return (0);
	return (data);
}
