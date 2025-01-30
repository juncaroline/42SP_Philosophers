/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:29:39 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/30 11:29:58 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo_group)
{
	int	i;

	i = 0;
	while (i < philo_group[0].total_philos)
	{
		pthread_mutex_lock(philo_group[i].meal_lock);
		if (get_current_time() - philo_group[i].time_last_meal
			>= philo_group[i].time_to_die && !philo_group[i].is_eating)
		{
			print_msg("died", &philo_group[i], philo_group[i].id);
			pthread_mutex_unlock(philo_group[i].meal_lock);
			pthread_mutex_lock(philo_group[0].dead_lock);
			*philo_group->dead = 1;
			pthread_mutex_unlock(philo_group[0].dead_lock);
			return (1);
		}
		pthread_mutex_unlock(philo_group[i].meal_lock);
		i++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philo_group)
{
	int	i;
	int	fed_count;

	i = 0;
	fed_count = 0;
	if (philo_group[0].meals_required == -1)
		return (0);
	while (i < philo_group[0].total_philos)
	{
		pthread_mutex_lock(philo_group[i].meal_lock);
		if (philo_group[i].meals_eaten >= philo_group[i].meals_required)
			fed_count++;
		pthread_mutex_unlock(philo_group[i].meal_lock);
		i++;
	}
	if (fed_count == philo_group[0].total_philos)
	{
		pthread_mutex_lock(philo_group[0].dead_lock);
		*philo_group->dead = 1;
		pthread_mutex_unlock(philo_group[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *ptr)
{
	t_philo	*philo_group;

	philo_group = (t_philo *)ptr;
	while (1)
	{
		if (check_death(philo_group) == 1 || check_if_all_ate(philo_group) == 1)
			break ;
		usleep(100);
	}
	return (ptr);
}
