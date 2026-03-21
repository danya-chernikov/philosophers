/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:47:31 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:55:16 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdlib.h>

#include <unistd.h>

void	join_threads(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		if (pthread_join(r->philos[i].thread, NULL) != 0)
			write(STDERR_FILENO, JOIN_TH_ERR, ft_strlen(JOIN_TH_ERR));
		++i;
	}
	if (pthread_join(r->monitor, NULL) != 0)
		write(STDERR_FILENO, JOIN_TH_ERR, ft_strlen(JOIN_TH_ERR));
}

void	cleanup_rules(t_rules *r)
{
	int	i;

	i = 0;
	while (i < r->num_philo)
	{
		pthread_mutex_destroy(&r->philos[i].meal_mtx);
		++i;
	}
	i = 0;
	while (i < r->num_philo)
	{
		pthread_mutex_destroy(&r->forks[i]);
		++i;
	}
	pthread_mutex_destroy(&r->print_mtx);
	pthread_mutex_destroy(&r->stop_mtx);
	free(r->forks);
	free(r->philos);
}
