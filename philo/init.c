/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:21 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 21:10:48 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>
#include <stdlib.h>

int	check_args(t_rules *r, int argc, char **argv)
{
	r->num_philo = ft_atoi(argv[1]);
	r->time_to_die = ft_atoi(argv[2]);
	r->time_to_eat = ft_atoi(argv[3]);
	r->time_to_sleep = ft_atoi(argv[4]);
	if (r->num_philo <= 0 || r->time_to_die <= 0)
		return (COMMON_FAILURE);
	if (r->time_to_eat <= 0 || r->time_to_sleep <= 0)
		return (COMMON_FAILURE);
	if (argc == 6)
	{
		r->ntimes_each_must_eat = ft_atoi(argv[5]);
		if (r->ntimes_each_must_eat <= 0)
			return (COMMON_FAILURE);
	}
	return (COMMON_SUCCESS);
}

void	assign_philo_ids(t_rules *r)
{
	int	pi;

	pi = 0;
	while (pi < r->num_philo)
	{
		r->philos[pi].id = pi + 1;
		r->philos[pi].meals_eaten = 0;
		r->philos[pi].last_meal_ms = 0;
		r->philos[pi].f_is_full = false;
		r->philos[pi].rules = r;
		r->philos[pi].left_fork = &r->forks[pi];
		r->philos[pi].right_fork = &r->forks[(pi + 1) % r->num_philo];
		++pi;
	}
}

void	init_defaults(t_rules *r)
{
	r->philos = NULL;
	r->forks = NULL;
	r->f_sim_stop = false;
	r->ntimes_each_must_eat = -1;
	r->start_ms = 0;
	r->full_count = 0;
}

int	alloc_data(t_rules *r)
{
	r->philos = (t_philo *)malloc(r->num_philo * sizeof (t_philo));
	if (!r->philos)
		return (write(2, MALLOC_ERR, ft_strlen(MALLOC_ERR)), COMMON_SYS_ERR);
	r->forks =
		(pthread_mutex_t *)malloc(r->num_philo * sizeof (pthread_mutex_t));
	if (!r->forks)
	{
		write(STDERR_FILENO, MALLOC_ERR, ft_strlen(MALLOC_ERR));
		free(r->philos);
		r->philos = NULL;
		return (COMMON_SYS_ERR);
	}
	return (COMMON_SUCCESS);
}
