/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:52:46 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/02 14:36:06 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(t_philo *philo, t_global_config *config)
{
	while (1)
	{
		pthread_mutex_lock(&config->mutex_eat);
		if (config->someone_died == 1 || config->all_philos_full == 1)
		{
			pthread_mutex_unlock(&config->mutex_eat);
			return (NULL);
		}
		pthread_mutex_unlock(&config->mutex_eat);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		if (config->max_meals > 0 && philo->meals_eaten >= config->max_meals)
		{
			ft_print_status(philo, "has eaten the required times");
			return (NULL);
		}
		sleep_and_think(philo);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_global_config	*config;

	philo = (t_philo *)arg;
	config = philo->config;
	if (check_single_philo(philo))
		return (NULL);
	pthread_mutex_lock(&config->mutex_eat);
	philo->last_meal_time = ft_get_current_time();
	pthread_mutex_unlock(&config->mutex_eat);
	return (philo_routine(philo, config));
}

void	*monitor_death(void *arg)
{
	t_philo			*philos;
	t_philo			*current;
	t_global_config	*config;

	philos = (t_philo *)arg;
	config = philos->config;
	while (!config->someone_died && !config->all_philos_full)
	{
		current = philos;
		while (current)
		{
			if (check_philo_death(config, current))
				return (NULL);
			current = current->next;
		}
		if (config->max_meals > 0 && check_all_full(config, philos))
			return (NULL);
		usleep(5000);
	}
	return (NULL);
}
