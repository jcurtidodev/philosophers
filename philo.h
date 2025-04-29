/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcurtido <jcurtido@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:29:45 by jcurtido          #+#    #+#             */
/*   Updated: 2025/04/02 14:45:52 by jcurtido         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_global_config
{
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_eat;
	int					num_philos;
	time_t				time_to_die;
	time_t				time_to_eat;
	time_t				time_to_sleep;
	int					max_meals;
	time_t				init_timestamp;
	int					someone_died;
	int					all_philos_full;
}	t_global_config;

typedef struct s_philo
{
	t_global_config	*config;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				meals_eaten;
	time_t			last_meal_time;
	struct s_philo	*next;
}	t_philo;

// Atoi
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

// Config
void		free_philos(t_philo *head);
t_philo		*create_philo(int id, t_global_config *config,
				pthread_mutex_t *forks);
int			init_config(t_global_config *condig, int ac, char *av[]);
int			init_philos(t_philo **philo_list, t_global_config *config,
				pthread_mutex_t *forks);

// Utils
time_t		ft_get_current_time(void);
void		ft_print_status(t_philo *philo, char *status);

// Utils Philo
int			check_single_philo(t_philo *philo);
int			check_philo_death(t_global_config *config, t_philo *philo);
int			check_all_full(t_global_config *config, t_philo *philo);

// Actions Philo
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);

// Philo
void		*monitor_death(void *arg);
void		*routine(void *arg);
int			entrance(int ac, char *av[]);
