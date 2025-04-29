/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:17:06 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/03 14:16:56 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->mutex_eat);
	ft_print_status(philo, "is eating");
	philo->last_meal_time = ft_get_current_time();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->config->mutex_eat);
	usleep(philo->config->time_to_eat * 1000);
}

void	sleep_and_think(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	usleep(philo->config->time_to_sleep * 1000);
	ft_print_status(philo, "is thinking");
}
