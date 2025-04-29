/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:27:00 by jcurtido          #+#    #+#             */
/*   Updated: 2025/03/10 16:06:03 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static int	invalid_args(void)
{
	char	*msg;
	char	*vars;

	msg = "Invalid args. Variables needed (all positive):\n";
	vars = "philosophers_num (>= 1)\n"
		"time_to_die (milliseconds)\n"
		"time_to_eat (milliseconds)\n"
		"time_to_sleep (milliseconds)\n"
		"number_of_times_each_philosopher_must_eat (optional)\n"
		"e.g. ./philo 5 200 200 200 3\n";
	return (printf("%s%s", msg, vars));
}

static int	check_inv_values(int ac, char *av[])
{
	int	i;

	i = 0;
	if (ac < 2 || ac < 5 || ac > 6 || ft_atoi(av[1]) < 1)
		return (1);
	while (ac > 2)
	{
		if (ft_atoi(av[ac - 1]) <= 0)
			return (1);
		while (av[ac - 1][i])
		{
			if (!ft_isdigit(av[ac - 1][i]))
				return (1);
			i++;
		}
		ac--;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	if (check_inv_values(ac, av))
		return (invalid_args());
	else
		entrance(ac, av);
	return (0);
}
