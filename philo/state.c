/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:34 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:55:27 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>

/* Getting simulation stop flag */
bool	get_sim_stop_flag(t_rules *r)
{
	bool	res;

	pthread_mutex_lock(&r->stop_mtx);
	res = r->f_sim_stop;
	pthread_mutex_unlock(&r->stop_mtx);
	return (res);
}

/* Setting simulation stop flag */
void	set_sim_stop_flag(t_rules *r, bool value)
{
	pthread_mutex_lock(&r->stop_mtx);
	r->f_sim_stop = value;
	pthread_mutex_unlock(&r->stop_mtx);
}

void	print_status(t_philo *p, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&p->rules->print_mtx);
	if (!get_sim_stop_flag(p->rules))
	{
		timestamp = now_ms() - p->rules->start_ms;
		printf("%ld %d %s\n", timestamp, p->id, msg);
	}
	pthread_mutex_unlock(&p->rules->print_mtx);
}
