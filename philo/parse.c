/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:11:16 by dchernik          #+#    #+#             */
/*   Updated: 2026/03/21 15:47:34 by dchernik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <unistd.h>

static int	is_pos_num(char *s);
static int	print_usage(char *prog);

int	check_argc_num(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (print_usage(argv[0]));
	i = 1;
	while (i < argc)
	{
		if (is_pos_num(argv[i]) != COMMON_SUCCESS)
			return (print_usage(argv[0]));
		++i;
	}
	return (COMMON_SUCCESS);
}

static int	is_pos_num(char *s)
{
	int	i;

	if (!s || !s[0])
		return (COMMON_FAILURE);
	i = 0;
	if (s[i] == '+')
		++i;
	if (!s[i])
		return (COMMON_FAILURE);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (COMMON_FAILURE);
		++i;
	}
	return (COMMON_SUCCESS);
}

static int	print_usage(char *prog)
{
	char	errbuf[MAX_ERRBUF];

	ft_strlcpy(errbuf, "Usage: ", MAX_ERRBUF);
	ft_strlcat(errbuf, prog, MAX_ERRBUF);
	ft_strlcat(errbuf, " number_of_philosophers ", MAX_ERRBUF);
	ft_strlcat(errbuf, "time_to_die time_to_eat time_to_sleep", MAX_ERRBUF);
	ft_strlcat(errbuf, " [number_of_times_each", MAX_ERRBUF);
	ft_strlcat(errbuf, "_philosopher_must_eat]", MAX_ERRBUF);
	write(STDERR_FILENO, errbuf, ft_strlen(errbuf));
	return (COMMON_FAILURE);
}
