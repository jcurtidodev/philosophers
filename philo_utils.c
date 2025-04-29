/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:55:37 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/02 14:42:39 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_single_philo(t_philo *philo)
{
	if (philo->config->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		usleep(philo->config->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	check_philo_death(t_global_config *config, t_philo *philo)
{
	long int	current_time;

	if (!philo)
		return (0);
	current_time = ft_get_current_time();
	pthread_mutex_lock(&config->mutex_eat);
	if ((current_time - philo->last_meal_time) > config->time_to_die)
	{
		ft_print_status(philo, "died");
		config->someone_died = 1;
		pthread_mutex_unlock(&config->mutex_eat);
		return (1);
	}
	pthread_mutex_unlock(&config->mutex_eat);
	return (0);
}

int	check_all_full(t_global_config *config, t_philo *philo)
{
	t_philo	*current;
	int		all_full;

	all_full = 1;
	current = philo;
	pthread_mutex_lock(&config->mutex_eat);
	while (current != NULL)
	{
		if (current->meals_eaten < config->max_meals)
		{
			all_full = 0;
			break ;
		}
		current = current->next;
	}
	if (all_full)
		config->all_philos_full = 1;
	pthread_mutex_unlock(&config->mutex_eat);
	return (all_full);
}
