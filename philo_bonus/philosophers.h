/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 02:22:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/08 16:20:13 by rude-jes         ###   ########.fr       */
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
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_garbcol
{
	void				*content;
	struct s_garbcol	*next;
	struct s_garbcol	*prev;
}						t_garbcol;

typedef struct s_philosopher
{
	int				id;
	bool			wait;
	bool			*is_someone_dead;
	bool			has_eaten;
	bool			has_think;
	pid_t			pid;
	pthread_t		reaper_thread;
	sem_t			*forks;
	sem_t			**write_lock;
	sem_t			**dead_lock;
	sem_t			**living_philos;
	int				*max_eat_counter;
	int				eat_counter;
	long			*time_to_die;
	long			*time_to_eat;
	long			*time_to_sleep;
	struct timeval	last_time_eating;
	struct timeval	*start_timeval;
}					t_philosopher;

typedef struct s_data
{
	pthread_t		hypervisor;
	int				number_of_philosophers;
	int				number_of_times_each_philosopher_must_eat;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	struct timeval	start_timeval;
	sem_t			*write_lock;
	sem_t			*dead_lock;
	sem_t			*living_philos;
	bool			is_dead;
	t_philosopher	**philosophers;
}					t_data;

//	FROM FILE utils/app_init.c

//		new_philosopher:	creates a new philosopher
t_philosopher	*new_philosopher(t_data *data);
//		app_init: initialize application data ad philosophers instances
//		returns t_data *struct
//		returns null if error
t_data			*app_init(int argc, char **argv);

//	FROM FILE utils/events_handler.c

//		check_death: checks philosopher death status using semaphores lockers
bool			check_death(t_philosopher *philosopher);
//		send_status: writes status message in console
void			send_status(t_philosopher *philosopher, char *status);

//	FROM FILE utils/exit_handler.c

//		unlink_sems: unlink all semaphores
void			unlink_sems(void);
//		secure_exit: clear garbage collector and returns 0
int				secure_exit(void);
//		error_exit: clear garbage collector and returns 1
int				error_exit(char *error);
//		crash_exit: clear garbage collector, prints error and returns 0
int				crash_exit(void);

//	FROM FILE utils/ft_utils_atoitoa.c

//		ft_itoa: converts long into an allocated string equivalent
char			*ft_itoa(long n);
//		ft_atoi: converts str into a long equivalent
long			ft_atoi(const char *str);

//	FROM FILE utils/ft_utils_mem.c
void			*ft_reallocf(void *ptr, size_t size, size_t newsize);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_substr(const char *s, unsigned int start, size_t len);

//	FROM FILE utils/ft_utils_str.c

//		ft_strlen: counts number of char of string without counting /0
size_t			ft_strlen(const char *s);
//		ft_strdup: str s copy to a new returned allocation
char			*ft_strdup(const char *s);
//		ft_strtrim: clear charset from start and end of string
char			*ft_strtrim(char const *s1, char const *set);
//		ft_strcmp: returns difference between s1 and s2
int				ft_strcmp(char *s1, char *s2);

//	FROM FILE utils/garbagecollector_cleaner.c

//		gfree: destroys the garbage node of specific address if exists
void			gfree(void *address);
//		cleargarbage: destroy garbage collector nodes and contents
void			cleargarbage(void);

//	FROM FILE utils/garbagecollector.c

//		getgarbage: get header of garbage collector
t_garbcol		**getgarbage(void);
//		addgarbage: add address to garbage collector
void			*addgarbage(void *address);
//		galloc: new allocation directly added to garbage collector
void			*galloc(size_t size);

// FROM FILE utils/hypervisor.c

//		check_finish: checks if philosophers have finished their meal
int				check_finish(t_philosopher *philosophers);
//		check_starving: checks if philosopher is starving
int				check_starving(t_philosopher *philosopher);
//		hypervisor: philosopher hypervisor
void			*hypervisor(void *param);

//	FROM FILE utils/parser.c

//		parse_pint: parse char *input into a int
//		returns positive int value
//		returns -1 in error
int				parse_pint(char *input);
//		init_simulation_limit: parse and set simulation limit
int				init_simulation_limit(t_data *data, int argc, char **argv);

//	FROM FILE utils/simulation.c

//		philsopher_routine: simulation routine to attach to a thread
void			*philosopher_routine(void *param);

//	FROM FILE utils/struct_init.c

//		init_forks: set left and right forks for each philosopher
sem_t			*init_forks(int nb_forks);
//		init_philosophers: init philosophers inside t_data struct
int				init_philosophers(t_data *data);

//	FROM FILE utils/time_utils.c

//		actual_time: returns current time in MS
long			actual_time(void);
//		get_difftimestamp: returns the difference between now and param
long			get_difftimestamp(struct timeval time);
//		get_timestamp: returns current timestamp in ms
long			get_timestamp(void);
//		mssleep: home made usleep function that waits the inteded time
void			mssleep(long time_in_ms);

#endif