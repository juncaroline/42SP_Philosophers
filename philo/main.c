/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:17:38 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/30 11:28:25 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philo_group[200];
	pthread_mutex_t	forks[200];

	if (ac == 5 || ac == 6)
	{
		if (check_valid_args(av) == 1)
			return (1);
		init_data(&data, philo_group);
		init_forks(forks, ft_atoi(av[1]));
		init_philos(philo_group, &data, forks, av);
		create_and_join(&data, forks);
		destroy_all(NULL, &data, forks);
	}
	else
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	return (0);
}
