/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:55:09 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/28 18:31:47 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

static void	init_input(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_eat = ft_atoi(av[5]);
	else
		philo->num_times_eat = -1;
}

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
	char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		init_input(&philos[i], av);
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].time_start = get_current_time();
		philos[i].time_last_meal = get_current_time();
		philos[i].print_lock = &data->print_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead_flag;
		philos[i].left_fork = &forks[i];
		if (i == 0)
			philos[i].right_fork = &forks[philos[i].num_of_philos - 1];
		else
			philos[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	destroy_all(char *msg, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (msg)
		write(2, msg, ft_strlen(msg));
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->print_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
