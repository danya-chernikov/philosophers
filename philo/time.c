/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:36 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:38:59 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>
#include <sys/time.h>

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

/* The idea is not to sleep in one big usleep(),
 * but to sleep in small chunks and regularly
 * check whether it is time to stop */
void	smart_sleep(t_rules *r, long ms)
{
	long	end;

	end = now_ms() + ms;
	while (!get_sim_stop_flag(r))
	{
		if (now_ms() >= end)
			break ;
		usleep(200);
	}
}

/* Wait for the common simulation start.
 * It makes all threads start working at
 * approximately the same time */
void	wait_start(t_rules *r)
{
	while (now_ms() < r->start_ms)
		usleep(100);
}
