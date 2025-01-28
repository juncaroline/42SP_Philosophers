/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:41:18 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/28 18:27:09 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (get_current_time() - philos[i].time_last_meal
			>= philos[i].time_to_die && philos[i].eating == 0)
		{
			print_msg("died", &philos[i], philos[i].id);
			pthread_mutex_unlock(philos[i].meal_lock);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philos[0].num_times_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_eat)
			ate++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (ate == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
	{
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
		usleep(100);
	}
	return (ptr);
}

int	create_thread(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	manager;
	int			i;

	if (pthread_create(&manager, NULL, &monitor, data->philos) != 0)
		destroy_all("Error creating monitor thread\n", data, forks);
	i = 0;
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			destroy_all("Error creating philosopher thread\n", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(manager, NULL) != 0)
		destroy_all("Error joining monitor thread\n", data, forks);
	while (i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_all("Error joining philosopher thread\n", data, forks);
		i++;
	}
	return (0);
}
