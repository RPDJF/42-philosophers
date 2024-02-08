/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:25:08 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 16:17:04 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_childs(t_philosopher **philosophers)
{
	while (*philosophers)
	{
		waitpid((*philosophers)->pid, 0, 0);
		philosophers++;
	}
}

static int	start_processes(t_data *data)
{
	t_philosopher	**philosophers;

	philosophers = data->philosophers;
	while (*philosophers)
	{
		sem_wait(data->living_philos);
		(*philosophers)->pid = fork();
		if ((*philosophers)->pid < 0)
			return (-1);
		else if ((*philosophers)->pid == 0)
		{
			philosopher_routine(*philosophers);
			exit(0);
		}
		else
			philosophers++;
	}
	pthread_create(&data->hypervisor, 0, hypervisor, data);
	wait_childs(data->philosophers);
	sem_post(data->living_philos);
	pthread_join(data->hypervisor, 0);
	return (0);
}

static int	start_philo(t_data *data)
{
	t_philosopher	**philosophers;

	if (start_processes(data) < 0)
		return (-1);
	philosophers = data->philosophers;
	while (*philosophers)
		waitpid((*(philosophers++))->pid, NULL, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	unlink_sems();
	if (argc < 5 || argc > 6)
		return (error_exit("Wrong usage."));
	data = app_init(argc, argv);
	if (!data)
		return (crash_exit());
	gettimeofday(&data->start_timeval, 0);
	data->write_lock = sem_open("WRITE_LOCK", O_CREAT | O_EXCL, 0666, 1);
	data->dead_lock = sem_open("DEAD_LOCK", O_CREAT | O_EXCL, 0666, 1);
	data->living_philos = sem_open("LIVING_LOCKER", O_CREAT | O_EXCL, 0666,
			data->number_of_philosophers);
	if (start_philo(data) < 0)
		return (crash_exit());
	return (secure_exit());
}
