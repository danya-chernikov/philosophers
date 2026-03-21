/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:30 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 21:11:10 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_full_state(t_philo *p);

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
 *     6. release both forks.
 *
 * As soon as the last philosopher reaches
 * `must_eat`, the `full_count` will be
 * equal to the `num_philo` and we immediately
 * put `f_sim_stop` in true */
void	eat_action(t_philo *p)
{
	lock_forks(p);
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	++p->meals_eaten;
	update_full_state(p);
	pthread_mutex_unlock(&p->meal_mtx);
	print_status(p, "is eating");
	smart_sleep(p->rules, p->rules->time_to_eat);
	unlock_forks(p);
}

static void	update_full_state(t_philo *p)
{
	if (p->rules->ntimes_each_must_eat < 0)
		return ;
	if (p->f_is_full || p->meals_eaten < p->rules->ntimes_each_must_eat)
		return ;
	p->f_is_full = true;
	pthread_mutex_lock(&p->rules->full_mtx);
	++p->rules->full_count;
	if (p->rules->full_count == p->rules->num_philo)
		set_sim_stop_flag(p->rules, true);
	pthread_mutex_unlock(&p->rules->full_mtx);
}
