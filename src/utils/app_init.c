/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:53:52 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:25:12 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_simulation_limit(t_data *data, int argc, char **argv)
{
	if (argc == 6)
	{
		data->number_of_times_each_philosopher_must_eat = parse_pint(argv[5]);
		if (data->number_of_times_each_philosopher_must_eat < 0)
			return (-1);
	}
	else
		data->number_of_times_each_philosopher_must_eat = -2;
	return (0);
}

t_data	*app_init(int argc, char **argv)
{
	t_data	*data;

	data = galloc(sizeof(t_data));
	if (!data)
		return (0);
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
	return (data);
}
