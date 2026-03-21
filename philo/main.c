/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:43:02 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:45:15 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (check_argc_num(argc, argv) != COMMON_SUCCESS)
		return (EXIT_FAILURE);
	if (init_rules(&rules, argc, argv) != COMMON_SUCCESS)
		return (EXIT_FAILURE);
	rules.start_ms = now_ms() + 20;
	if (start_threads(&rules) != COMMON_SUCCESS)
	{
		cleanup_rules(&rules);
		return (EXIT_FAILURE);
	}
	join_threads(&rules);
	cleanup_rules(&rules);
	return (EXIT_SUCCESS);
}
