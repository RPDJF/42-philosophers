/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:22:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/30 00:16:54 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	bool			*is_someone_dead;
	bool			has_eaten;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	int				*time_to_die;
	int				*time_to_eat;
	int				*time_to_sleep;
}		t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	bool			is_dead;
	t_philosopher	**philosophers;
}						t_data;

//	FROM FILE utils/app_init.c

//		app_init: initialize application data ad philosophers instances
//		returns t_data *struct
//		returns null if error
t_data	*app_init(int argc, char **argv);

//	FROM FILE utils/events_handler.c

//		update_death: update philosopher death status using mutex lockers
void	update_death(t_philosopher *philosopher, bool status);
//		check_death: checks current philosopher death status using mutex lockers
bool	check_death(t_philosopher *philosopher);

//	FROM FILE utils/exit_handler.c

//		secure_exit: clear garbage collector and returns 0
int		secure_exit(void);
//		error_exit: clear garbage collector and returns 1
int		error_exit(void);
//		crash_exit: clear garbage collector, prints error and returns 0
int		crash_exit(void);

//	FROM FILE utils/ft_utils_atoitoa.c

//		ft_itoa: converts int into allocated string equivalent
char	*ft_itoa(int n);
//		ft_atoi: converts str into an int equivalent
int		ft_atoi(const char *str);

//	FROM FILE utils/ft_utils_mem.c
void	*ft_reallocf(void *ptr, size_t size, size_t newsize);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);

//	FROM FILE utils/ft_utils_str.c

//		ft_strlen: counts number of char of string without counting /0
size_t	ft_strlen(const char *s);
//		ft_strdup: str s copy to a new returned allocation
char	*ft_strdup(const char *s);
//		ft_strtrim: clear charset from start and end of string
char	*ft_strtrim(char const *s1, char const *set);
//		ft_strcmp: returns difference between s1 and s2
int		ft_strcmp(char *s1, char *s2);

//	FROM FILE utils/parser.c

//		parse_pint: parse char *input into a int
//		returns positive int value
//		returns -1 in error
int		parse_pint(char *input);

#endif