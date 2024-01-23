/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:33:15 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*new_philosopher(t_data *data)
{
	t_philosopher	*philosopher;

	philosopher = galloc(sizeof(t_philosopher));
	if (!philosopher)
		return (0);
	philosopher->time_to_die = data->time_to_die;
	philosopher->time_to_eat = data->time_to_eat;
	philosopher->time_to_sleep = data->time_to_sleep;
	return (philosopher);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (1);
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	return (secure_exit());
}
