/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:17:38 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/27 09:29:15 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];

	if (ac == 5 || ac == 6)
	{
		if (check_valid_args(av) == 1)
			return (1);
		init_data(&data, philos);
		init_forks(forks, ft_atoi(av[1]));
		init_philos(philos, &data, forks, av);
	}
	else
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	return (0);
}
