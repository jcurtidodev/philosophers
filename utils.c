/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:44:46 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/02 14:07:40 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_print_status(t_philo *philo, char *status)
{
	time_t	time;

	pthread_mutex_lock(&philo->config->mutex_print);
	if (philo->config->someone_died == 1)
	{
		pthread_mutex_unlock(&philo->config->mutex_print);
		return ;
	}
	time = ft_get_current_time() - philo->config->init_timestamp;
	if (philo->config->someone_died == 0)
		printf("%ld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->config->mutex_print);
}
