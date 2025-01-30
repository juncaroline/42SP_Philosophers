/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:09:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/30 14:28:06 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args_received(char *av)
{
	int	i;

	i = 0;
	if (!av || !av[0])
		return (0);
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_args(char *av, int min, int max, const char *msg)
{
	int	value_received;

	if (!check_args_received(av))
		return (write(2, msg, ft_strlen(msg)), 1);
	value_received = ft_atoi(av);
	if (value_received < min || value_received > max)
		return (write(2, msg, ft_strlen(msg)), 1);
	return (0);
}

int	check_valid_args(char **av)
{
	if (validate_args(av[1], 1, 200, "Invalid number of philosophers\n"))
		return (1);
	if (validate_args(av[2], 1, INT_MAX, "Invalid time to die\n"))
		return (1);
	if (validate_args(av[3], 1, INT_MAX, "Invalid time to eat\n"))
		return (1);
	if (validate_args(av[4], 1, INT_MAX, "Invalid time to sleep\n"))
		return (1);
	if (av[5] && validate_args(av[5], 0, INT_MAX,
			"Invalid number of times each philosopher must eat\n"))
		return (1);
	return (0);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->time_start;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_lock);
}
