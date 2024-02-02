/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:53:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/02 09:50:34 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void	init_forks(t_data *data, t_philosopher *philosopher, int id)
{
	pthread_mutex_init(&philosopher->fork, 0);
	pthread_mutex_init(&philosopher->eat_lock, 0);
	philosopher->write_lock = &data->write_lock;
	if (id - 1 > 0)
	{
		philosopher->l_fork = &data->philosophers[id - 2]->fork;
		data->philosophers[id - 2]->r_fork = &philosopher->fork;
	}
	else
		philosopher->l_fork = 0;
	if (id != 1 && id == data->number_of_philosophers)
	{
		data->philosophers[0]->l_fork = &philosopher->fork;
		philosopher->r_fork = &data->philosophers[0]->fork;
	}
	else if (id == 1 && id == data->number_of_philosophers)
		philosopher->r_fork = 0;
}

static t_philosopher	*new_philosopher(t_data *data)
{
	t_philosopher	*philosopher;
	static int		id;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (0);
	philosopher->id = ++id;
	philosopher->has_think = false;
	philosopher->is_eating = false;
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

static int	init_philosophers(t_data *data)
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

static int	init_simulation_limit(t_data *data, int argc, char **argv)
{
	if (argc == 6)
	{
		data->number_of_times_each_philosopher_must_eat = parse_pint(argv[5]);
		if (data->number_of_times_each_philosopher_must_eat < 0)
			return (-1);
	}
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}

static t_data	*destroy_data(t_data *data)
{
	t_philosopher	**head;

	head = data->philosophers;
	if (head)
	{
		while (*head)
		{
			free(*head);
			head++;
		}
	}
	free(data->philosophers);
	free(data);
	return (0);
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
		return (destroy_data(data));
	data->time_to_die = parse_pint(argv[2]);
	if (data->time_to_die < 0)
		return (destroy_data(data));
	data->time_to_eat = parse_pint(argv[3]);
	if (data->time_to_eat < 0)
		return (destroy_data(data));
	data->time_to_sleep = parse_pint(argv[4]);
	if (data->time_to_sleep < 0)
		return (destroy_data(data));
	if (init_simulation_limit(data, argc, argv) < 0)
		return (destroy_data(data));
	if (init_philosophers(data) < 0)
		return (destroy_data(data));
	return (data);
}
