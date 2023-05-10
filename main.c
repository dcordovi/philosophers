/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:15:57 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 10:19:04 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_vars(int argc, char **argv)
{
	int	i;

	i = 0;
	vars()->nb_philos = ft_atoi(argv[1]);
	vars()->time_die = ft_atoi(argv[2]);
	vars()->time_eat = ft_atoi(argv[3]);
	vars()->time_sleep = ft_atoi(argv[4]);
	vars()->start_time = get_time();
	vars()->all_alive = 1;
	vars()->all_starve = vars()->nb_philos;
	vars()->has_limit = 0;
	vars()->nbr_eat = -1;
	fill_locked();
	if (argc == 6)
	{
		vars()->nbr_eat = ft_atoi(argv[5]);
		vars()->has_limit = 1;
	}
	while (i < vars()->nb_philos)
	{
		vars()->philos[i].i = i;
		vars()->philos[i].times_eaten = 0;
		vars()->philos[i].last_eat = 0;
		i++;
	}
}

void	*routine(void *args)
{
	t_philo	philo;

	philo = *(t_philo *)args;
	while (check_all_alive())
	{
		eat(&philo);
		if (vars()->has_limit && philo.times_eaten == vars()->nbr_eat)
		{
			pthread_mutex_lock(&vars()->starve);
			vars()->all_starve--;
			pthread_mutex_unlock(&vars()->starve);
			break ;
		}
		if (check_all_alive() == 0)
			break ;
		sleep_philo(&philo);
		if (check_all_alive() == 0)
			break ;
		think(&philo);
	}
	return (NULL);
}

void	*checker(void)
{
	int	i;

	while (check_all_alive() && check_all_starve())
	{
		i = 0;
		while (i < vars()->nb_philos && check_all_alive())
		{
			pthread_mutex_lock(&vars()->eat[i]);
			if (time_after() - \
vars()->philos[i].last_eat >= (uint64_t)vars()->time_die)
			{
				pthread_mutex_lock(&vars()->alive);
				vars()->all_alive = 0;
				pthread_mutex_unlock(&vars()->alive);
				unlock_mutexes();
				pthread_mutex_unlock(&vars()->eat[i]);
				break ;
			}
			pthread_mutex_unlock(&vars()->eat[i]);
			i++;
		}
	}
	if (!(vars()->has_limit && !vars()->all_starve))
		lock_print(time_after(), vars()->philos[i].i + 1, "died");
	return (NULL);
}

int	init_mutexes(void)
{
	int	i;

	i = 0;
	initialize_forks();
	if (create_threads() != 0)
		return (1);
	while (i < vars()->nb_philos)
	{
		if (pthread_join(vars()->th[i], NULL) != 0)
			return (2);
		i++;
	}
	if (pthread_join(vars()->t_checker, NULL) != 0)
		return (2);
	destroy_forks();
	return (0);
}

int	main(int argc, char **argv)
{
	if (non_numeric(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || \
ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
		return (1);
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
			return (1);
	}
	if (ft_atoi(argv[1]) == 1)
		return (one_philo(ft_atoi(argv[2])));
	if (argc < 5 || argc > 6)
		return (1);
	assign_vars(argc, argv);
	init_mutexes();
	return (1);
}
