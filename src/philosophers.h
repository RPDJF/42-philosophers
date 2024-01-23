/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:22:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 03:59:36 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include "../libs/betterft/betterft.h"

typedef struct s_philosopher
{
	pthread_t	thread;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
}		t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;		
	t_philosopher	**philosophers;
}		t_data;

//	FROM FILE utils/app_init.c

//		app_init: initialize application data
//		returns t_data *struct
//		returns null if error
t_data	*app_init(int argc, char **argv);

//	FROM FILE utils/parser.c

//		parse_pint: parse char *input into a int
//		returns positive int value
//		returns -1 in error
int		parse_pint(char *input);

#endif