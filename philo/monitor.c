/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:28 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 21:09:59 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

#include <stdio.h>

static bool	philo_died(t_rules *r, int i);

/* The monitor runs in a loop and checks:
 *     whether anyone has died, and
 *     whether everyone has reached `ntimes_each_must_eat` */
void	*monitor_routine(void *arg)
{
	int		pi;
	t_rules	*r;

	r = (t_rules *)arg;
	wait_start(r);
	while (!get_sim_stop_flag(r))
	{
		pi = 0;
		while (pi < r->num_philo)
		{
			if (philo_died(r, pi))
				return (NULL);
			++pi;
		}
		usleep(500);
	}
	return (NULL);
}

void	print_death(t_philo *p)
{
	long	timestamp;

	pthread_mutex_lock(&p->rules->print_mtx);
	timestamp = now_ms() - p->rules->start_ms;
	printf("%ld %d died\n", timestamp, p->id);
	pthread_mutex_unlock(&p->rules->print_mtx);
}

static bool	philo_died(t_rules *r, int i)
{
	long	last_meal;

	pthread_mutex_lock(&r->philos[i].meal_mtx);
	last_meal = r->philos[i].last_meal_ms;
	pthread_mutex_unlock(&r->philos[i].meal_mtx);
	if (now_ms() - last_meal <= r->time_to_die)
		return (false);
	set_sim_stop_flag(r, true);
	print_death(&r->philos[i]);
	return (true);
}
