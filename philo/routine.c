/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:27 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:39:09 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	wait_start(p->rules);
	if (p->rules->num_philo == 1)
		return (one_philo(p), NULL);
	if (p->id % 2 == 0)
		usleep(1000);
	while (!get_sim_stop_flag(p->rules))
	{
		eat_action(p);
		if (get_sim_stop_flag(p->rules))
			break ;
		print_status(p, "is sleeping");
		smart_sleep(p->rules, p->rules->time_to_sleep);
		if (get_sim_stop_flag(p->rules))
			break ;
		print_status(p, "is thinking");
	}
	return (NULL);
}

void	one_philo(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_status(p, "has taken a fork");
	while (!get_sim_stop_flag(p->rules))
		usleep(200);
	pthread_mutex_unlock(p->left_fork);
}
