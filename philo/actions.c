/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:30 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 14:02:31 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_forks(t_philo *p)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (p->id % 2 == 0)
	{
		first = p->left_fork;
		second = p->right_fork;
	}
	else
	{
		first = p->right_fork;
		second = p->left_fork;
	}
	pthread_mutex_lock(first);
	print_status(p, "has taken a fork");
	pthread_mutex_lock(second);
	print_status(p, "has taken a fork");
}

void	unlock_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

/* Here we just:
 *     1. take both forks;
 *     2. update last_meal_ms;
 *     3. increment meals_eaten;
 *     4. print log message;
 *     5. wait for t_eat milliseconds;
 *     6. release both forks. */
void	eat_action(t_philo *p)
{
	lock_forks(p);
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	++p->meals_eaten;
	pthread_mutex_unlock(&p->meal_mtx);
	print_status(p, "is eating");
	smart_sleep(p->rules, p->rules->time_to_eat);
	unlock_forks(p);
}
