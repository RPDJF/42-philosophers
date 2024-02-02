/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:53:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 20:56:23 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_philosopher	*new_philosopher(t_data *data)
{
	t_philosopher	*philosopher;
	static int		id;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (0);
	philosopher->id = ++id;
	if (id % 2)
		philosopher->wait = false;
	else
		philosopher->wait = true;
	philosopher->eat_counter = 0;
	philosopher->max_eat_counter
		= &data->number_of_times_each_philosopher_must_eat;
	philosopher->write_lock = &data->write_lock;
	philosopher->has_think = false;
	gettimeofday(&philosopher->last_time_eating, NULL);
	philosopher->start_timeval = &data->start_timeval;
	init_forks(data, philosopher, id);
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

	data = malloc(sizeof(t_data));
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
