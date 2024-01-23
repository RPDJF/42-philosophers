/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 05:56:01 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*start_routine(void *param)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)param;
	ft_printf("Je suis le %dième philosopher !\n", philosopher->id);
	return (0);
}

static int	start_threads(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		if (pthread_create(&(*philosophers)->thread, NULL, start_routine, *philosophers))
			return (-1);
		(*philosophers)++;
	}
	return (0);
}

static int	start_philo(t_data *data)
{
	if (start_threads(data->philosophers) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (error_exit());
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	if (start_philo(data) < 0)
		return (crash_exit());
	start_philo(data);
	return (secure_exit());
}
