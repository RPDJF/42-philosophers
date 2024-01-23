/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:22:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:47:52 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include "../libs/betterft/betterft.h"

typedef struct s_philosopher
{
	int			id;
	pthread_t	thread;
	bool		fork;
	bool		*l_fork;
	bool		*r_fork;
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

//		app_init: initialize application data ad philosophers instances
//		returns t_data *struct
//		returns null if error
t_data	*app_init(int argc, char **argv);

//	FROM FILE utils/exit_handler.c

//	secure_exit: clear garbage collector and returns 0
int		secure_exit(void);
//	error_exit: clear garbage collector and returns 1
int		error_exit(void);
//	crash_exit: clear garbage collector, prints error and returns 0
int		crash_exit(void);

//	FROM FILE utils/parser.c

//		parse_pint: parse char *input into a int
//		returns positive int value
//		returns -1 in error
int		parse_pint(char *input);

#endif