/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabo-ram <cabo-ram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:17:08 by cabo-ram          #+#    #+#             */
/*   Updated: 2025/01/28 16:57:17 by cabo-ram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_eat;
	int				*dead;
	size_t			time_start;
	size_t			time_last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
}	t_philo;

typedef struct s_data
{
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	int				dead_flag;
	t_philo			*philos;
}	t_data;

//check.c
int		check_valid_args(char **av);
void	print_msg(char *str, t_philo *philo, int id);
int		dead_loop(t_philo *philo);

//init_end.c
void	init_data(t_data *data, t_philo *philos);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks,
			char **av);
void	destroy_all(char *str, t_data *data, pthread_mutex_t *forks);

//routine.c
void	*philo_routine(void *ptr);

//threads.c
int		check_if_dead(t_philo *philos);
int		check_if_all_ate(t_philo *philos);
void	*philo_routine(void *ptr);
int		create_thread(t_data *data, pthread_mutex_t *forks);

//utils.c
int		ft_atoi(const char *str);
int		ft_strlen(const char *str);
int		custom_usleep(unsigned long req_time);
size_t	get_current_time(void);

#endif