/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:43:06 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 20:54:48 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>

# define COMMON_SUCCESS	1
# define COMMON_FAILURE	0
# define COMMON_SYS_ERR	-1

# define MAX_ERRBUF		1024
# define MALLOC_ERR		"Error: malloc()\n"
# define MUTEX_ERR		"Error: pthread_mutex_init()\n"
# define CREATE_TH_ERR	"Error: pthread_create()\n"
# define JOIN_TH_ERR	"Error: pthread_join()\n"

typedef struct s_rules	t_rules;

/* Stores each philosopher state.
 *     last_meal_ms - the time in milliseconds
 *					  when the philosopher last
 *					  started eating; */
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_ms;
	bool			f_is_full;
	pthread_t		thread;
	pthread_mutex_t	meal_mtx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

/* Stores common simulation parameters.
 *     start_ms   - the absolute simulation start
 *				    time in milliseconds;
 *     f_sim_stop - simulation stop flag.
 *					0 - simulation continues,
 *					1 - simulation should be stopped;
 *     full_count - how many philosophers are already full */
typedef struct s_rules
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			ntimes_each_must_eat;
	long			start_ms;
	int				full_count;
	bool			f_sim_stop;
	pthread_t		monitor;
	pthread_mutex_t	full_mtx;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_rules;

/* parse.c */
int		check_argc_num(int argc, char **argv);

/* init.c */
int		init_rules(t_rules *r, int argc, char **argv);
int		init_mutexes(t_rules *r);
void	assign_philo_ids(t_rules *r);
int		check_args(t_rules *r, int argc, char **argv);

/* init2.c */
int		init_mutexes(t_rules *r);
int		init_rules(t_rules *r, int argc, char **argv);
void	init_defaults(t_rules *r);
int		alloc_data(t_rules *r);

/* start.c */
int		start_threads(t_rules *r);

/* state.c */
bool	get_sim_stop_flag(t_rules *r);
void	set_sim_stop_flag(t_rules *r, bool value);
void	print_status(t_philo *p, char *msg);

/* time.c */
long	now_ms(void);
void	smart_sleep(t_rules *r, long ms);
void	wait_start(t_rules *r);

/* actions.c */
void	lock_forks(t_philo *p);
void	unlock_forks(t_philo *p);
void	eat_action(t_philo *p);

/* routine.c */
void	*philo_routine(void *arg);
void	one_philo(t_philo *p);

/* monitor.c */
void	*monitor_routine(void *arg);
void	print_death(t_philo *p);

/* cleanup.c */
void	join_threads(t_rules *r);
void	cleanup_rules(t_rules *r);

/* ft_aux.c */
int		ft_atoi(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);

#endif
