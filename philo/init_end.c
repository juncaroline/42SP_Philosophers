/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:55:09 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/29 14:43:16 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, t_philo *philos)
{
	data->is_dead = 0;
	data->philo_group = philos;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
		pthread_mutex_init(&forks[i++], NULL);
}

static void	convert_input(t_philo *philo, char **av)
{
	philo->total_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->meals_required = ft_atoi(av[5]);
	else
		philo->meals_required = -1;
}

void	init_philos(t_philo *philo_group, t_data *data, pthread_mutex_t *forks,
	char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo_group[i].id = i + 1;
		convert_input(&philo_group[i], av);
		philo_group[i].is_eating = 0;
		philo_group[i].meals_eaten = 0;
		philo_group[i].time_start = get_current_time();
		philo_group[i].time_last_meal = get_current_time();
		philo_group[i].print_lock = &data->print_lock;
		philo_group[i].dead_lock = &data->dead_lock;
		philo_group[i].meal_lock = &data->meal_lock;
		philo_group[i].dead = &data->is_dead;
		philo_group[i].left_fork = &forks[i];
		philo_group[i].right_fork = &forks[(i - 1
				+ philo_group[i].total_philos) % philo_group[i].total_philos];
		i++;
	}
}

void	destroy_all(char *msg, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (data)
	{
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->meal_lock);
		pthread_mutex_destroy(&data->print_lock);
		if (forks)
		{
			while (i < data->philo_group[0].total_philos)
				pthread_mutex_destroy(&forks[i++]);
		}
	}
}
