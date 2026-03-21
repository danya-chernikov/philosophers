/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:12:29 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 21:00:02 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>
#include <stdlib.h>

static int	mutex_fail(void);
static int	fail_forks(t_rules *r, int i);
static int	fail_meals(t_rules *r, int i);

int	init_mutexes(t_rules *r)
{
	int	i;

	if (pthread_mutex_init(&r->stop_mtx, NULL) != 0)
		return (mutex_fail());
	if (pthread_mutex_init(&r->print_mtx, NULL) != 0)
		return (pthread_mutex_destroy(&r->stop_mtx), mutex_fail());
	if (pthread_mutex_init(&r->full_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&r->print_mtx);
		pthread_mutex_destroy(&r->stop_mtx);
		return (mutex_fail());
	}
	i = 0;
	while (i < r->num_philo)
		if (pthread_mutex_init(&r->forks[i++], NULL) != 0)
			return (fail_forks(r, i));
	i = 0;
	while (i < r->num_philo)
		if (pthread_mutex_init(&r->philos[i++].meal_mtx, NULL) != 0)
			return (fail_meals(r, i));
	return (COMMON_SUCCESS);
}

int	init_rules(t_rules *r, int argc, char **argv)
{
	init_defaults(r);
	if (check_args(r, argc, argv) != COMMON_SUCCESS)
		return (COMMON_FAILURE);
	if (alloc_data(r) != COMMON_SUCCESS)
		return (COMMON_SYS_ERR);
	assign_philo_ids(r);
	if (init_mutexes(r) != COMMON_SUCCESS)
	{
		free(r->forks);
		free(r->philos);
		return (COMMON_SYS_ERR);
	}
	return (COMMON_SUCCESS);
}

static int	mutex_fail(void)
{
	write(STDERR_FILENO, MUTEX_ERR, ft_strlen(MUTEX_ERR));
	return (COMMON_SYS_ERR);
}

static int	fail_forks(t_rules *r, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&r->forks[i]);
	pthread_mutex_destroy(&r->print_mtx);
	pthread_mutex_destroy(&r->stop_mtx);
	pthread_mutex_destroy(&r->full_mtx);
	return (mutex_fail());
}

static int	fail_meals(t_rules *r, int i)
{
	while (--i >= 0)
		pthread_mutex_destroy(&r->philos[i].meal_mtx);
	i = r->num_philo;
	while (--i >= 0)
		pthread_mutex_destroy(&r->forks[i]);
	pthread_mutex_destroy(&r->print_mtx);
	pthread_mutex_destroy(&r->stop_mtx);
	pthread_mutex_destroy(&r->full_mtx);
	return (mutex_fail());
}
