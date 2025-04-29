/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:09:39 by jcurtido          #+#    #+#             */
/*   Updated: 2025/03/18 19:28:52 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

static void	free_all(t_global_config *config, t_philo *philo_list,
			pthread_t *philos, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&config->mutex_print);
	i = 0;
	while (i < config->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free_philos(philo_list);
	free(philos);
	free(forks);
}

static int	init_and_run_philos(t_global_config *config, pthread_mutex_t *forks,
			pthread_t *philos, t_philo **philo_list)
{
	pthread_t	monitor_thread;
	t_philo		*current;
	int			i;

	i = 0;
	while (i < config->num_philos)
		pthread_mutex_init(&forks[i++], NULL);
	if (init_philos(philo_list, config, forks))
		return (1);
	current = *philo_list;
	i = 0;
	while (current)
	{
		pthread_create(&philos[i++], NULL, routine, current);
		current = current->next;
	}
	pthread_create(&monitor_thread, NULL, monitor_death, *philo_list);
	i = 0;
	while (i < config->num_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

int	entrance(int ac, char *av[])
{
	t_global_config	config;
	pthread_mutex_t	*forks;
	pthread_t		*philos;
	t_philo			*philo_list;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	philo_list = NULL;
	if (!forks || !philos)
	{
		free(forks);
		free(philos);
		return (1);
	}
	if (init_config(&config, ac, av))
		return (free(forks), free(philos), 1);
	if (init_and_run_philos(&config, forks, philos, &philo_list))
		return (free(forks), free(philos), 1);
	free_all(&config, philo_list, philos, forks);
	return (0);
}
