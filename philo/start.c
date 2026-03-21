/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:25 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:54:41 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

static void	set_start_meals(t_rules *r);
static void	join_created(t_rules *r, int count);
static int	create_philos(t_rules *r);

/* Here we create threads for each
 * philosoher and monitor thread */
int	start_threads(t_rules *r)
{
	set_start_meals(r);
	if (create_philos(r) != COMMON_SUCCESS)
		return (COMMON_SYS_ERR);
	if (pthread_create(&r->monitor, NULL, monitor_routine, r) != 0)
	{
		write(STDERR_FILENO, CREATE_TH_ERR, ft_strlen(CREATE_TH_ERR));
		set_sim_stop_flag(r, true);
		join_created(r, r->num_philo);
		return (COMMON_SYS_ERR);
	}
	return (COMMON_SUCCESS);
}

static void	set_start_meals(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		r->philos[i].last_meal_ms = r->start_ms;
		++i;
	}
}

static void	join_created(t_rules *r, int count)
{
	while (--count >= 0)
		pthread_join(r->philos[count].thread, NULL);
}

static int	create_philos(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		if (pthread_create(&r->philos[i].thread, NULL,
			philo_routine, &r->philos[i]) != 0)
		{
			write(STDERR_FILENO, CREATE_TH_ERR, ft_strlen(CREATE_TH_ERR));
			set_sim_stop_flag(r, true);
			join_created(r, i);
			return (COMMON_SYS_ERR);
		}
		++i;
	}
	return (COMMON_SUCCESS);
}
