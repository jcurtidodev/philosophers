/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:43:37 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/02 14:25:20 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_philo *head)
{
	t_philo	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

t_philo	*create_philo(int id, t_global_config *config, pthread_mutex_t *forks)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->last_meal_time = ft_get_current_time();
	philo->meals_eaten = 0;
	philo->left_fork = &forks[id - 1];
	philo->right_fork = &forks[id % config->num_philos];
	philo->config = config;
	philo->next = NULL;
	return (philo);
}

int	init_config(t_global_config *config, int ac, char *av[])
{
	config->num_philos = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	config->init_timestamp = ft_get_current_time();
	config->someone_died = 0;
	config->all_philos_full = 0;
	if (ac == 6)
		config->max_meals = ft_atoi(av[5]);
	else
		config->max_meals = -1;
	if (pthread_mutex_init(&config->mutex_print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&config->mutex_eat, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_philo **philo_list, t_global_config *config,
		pthread_mutex_t *forks)
{
	t_philo	*head;
	t_philo	*current;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (i < config->num_philos)
	{
		*philo_list = create_philo(++i, config, forks);
		if (!*philo_list)
			return (free_philos(head), 1);
		if (!head)
		{
			head = *philo_list;
			current = head;
		}
		else
		{
			current->next = *philo_list;
			current = current->next;
		}
	}
	*philo_list = head;
	return (0);
}
