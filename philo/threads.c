/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:41:18 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/30 11:47:31 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	create_thread(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	manager;
	int			i;

	if (pthread_create(&manager, NULL, &monitor, data->philo_group) != 0)
		destroy_all("Error creating monitor thread\n", data, forks);
	i = 0;
	while (i < data->philo_group[0].total_philos)
	{
		if (pthread_create(&data->philo_group[i].thread, NULL, &philo_routine,
				&data->philo_group[i]) != 0)
			destroy_all("Error creating philosopher thread\n", data, forks);
		i++;
	}
	i = 0;
	if (pthread_join(manager, NULL) != 0)
		destroy_all("Error joining monitor thread\n", data, forks);
	while (i < data->philo_group[0].total_philos)
	{
		if (pthread_join(data->philo_group[i].thread, NULL) != 0)
			destroy_all("Error joining philosopher thread\n", data, forks);
		i++;
	}
	return (0);
}*/

static int	create_thread(t_data *data, pthread_mutex_t *forks,
	pthread_t *manager)
{
	int	i;

	if (pthread_create(manager, NULL, *monitor, data->philo_group) != 0)
	{
		destroy_all("Error creating monitor thread\n", data, forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_group[0].total_philos)
	{
		if (pthread_create(&data->philo_group[i].thread, NULL, &philo_routine,
				&data->philo_group[i]) != 0)
		{
			write(2, "Error creating philosopher thread\n", 34);
			while (--i >= 0)
				pthread_join(data->philo_group[i].thread, NULL);
			pthread_join(*manager, NULL);
			destroy_all(NULL, data, forks);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	join_thread(t_data *data, pthread_mutex_t *forks, pthread_t manager)
{
	int	i;

	if (pthread_join(manager, NULL) != 0)
	{
		write(2, "Error joining monitor thread\n", 29);
		destroy_all(NULL, data, forks);
		return (1);
	}
	i = 0;
	while (i < data->philo_group[0].total_philos)
	{
		if (pthread_join(data->philo_group[i].thread, NULL) != 0)
		{
			write(2, "Error joining philosopher thread\n", 33);
			destroy_all(NULL, data, forks);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_and_join(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	manager;

	if (create_thread(data, forks, &manager) != 0)
		return (1);
	if (join_thread(data, forks, manager) != 0)
		return (1);
	return (0);
}
