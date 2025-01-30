/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 16:09:27 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/30 14:27:48 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	if (dead_loop(philo))
		return ;
	if (philo->total_philos == 1)
	{
		custom_usleep(philo->time_to_die);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo, philo->id);
	philo->is_eating = 1;
	print_msg("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->time_last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	custom_usleep(philo->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	napping(t_philo *philo)
{
	print_msg("is sleeping", philo, philo->id);
	custom_usleep(philo->time_to_sleep);
}

static void	think(t_philo *philo)
{
	print_msg("is thinking", philo, philo->id);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		custom_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		napping(philo);
		think(philo);
	}
	return (NULL);
}
