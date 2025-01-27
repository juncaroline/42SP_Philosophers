/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:09:20 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/27 09:29:59 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args_received(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
			return (1);
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_valid_args(char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0
		|| check_args_received(av[1]) == 1)
		return (write (2, "Invalid number of philosophers\n", 31), 1);
	if (ft_atoi(av[2]) <= 0 || check_args_received(av[2]) == 1)
		return (write (2, "Invalid time to die\n", 20), 1);
	if (ft_atoi(av[3]) <= 0 || check_args_received(av[3]) == 1)
		return (write (2, "Invalid time to eat\n", 20), 1);
	if (ft_atoi(av[4]) <= 0 || check_args_received(av[4]) == 1)
		return (write (2, "Invalid time to sleep\n", 22), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_args_received(av[5]) == 1))
		return (write (2, "Invalid number of times each philosopher must eat\n",
				50), 1);
	return (0);
}

static int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->time_start;
	if (!dead_loop(philo))
		printf("%zu %d  %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_lock);
}