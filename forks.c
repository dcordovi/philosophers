/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:28:06 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 09:35:51 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(void)
{
	int	i;

	i = 0;
	while (i < vars()->nb_philos)
	{
		if (pthread_create(vars()->th + i, NULL, routine, \
vars()->philos + i) != 0)
			return (1);
		i += 2;
		ft_usleep(1);
	}
	ft_usleep(2);
	i = 1;
	while (i < vars()->nb_philos)
	{
		if (pthread_create(vars()->th + i, NULL, routine, \
vars()->philos + i) != 0)
			return (1);
		i += 2;
		ft_usleep(1);
	}
	if (pthread_create(&vars()->t_checker, NULL, (void *)checker, NULL) != 0)
		return (1);
	return (0);
}

void	initialize_forks(void)
{
	int	i;

	i = 0;
	while (i < vars()->nb_philos)
	{
		pthread_mutex_init(&vars()->forks[i], NULL);
		pthread_mutex_init(&vars()->eat[i], NULL);
		i++;
	}
	pthread_mutex_init(&vars()->alive, NULL);
	pthread_mutex_init(&vars()->starve, NULL);
	pthread_mutex_init(&vars()->lock, NULL);
}

void	destroy_forks(void)
{
	int	i;

	i = 0;
	while (i < vars()->nb_philos)
	{
		pthread_mutex_destroy(&vars()->forks[i]);
		pthread_mutex_destroy(&vars()->eat[i]);
		i++;
	}
	pthread_mutex_destroy(&vars()->alive);
	pthread_mutex_destroy(&vars()->starve);
	pthread_mutex_destroy(&vars()->lock);
}

void	unlock_mutexes(void)
{
	int	i;

	i = 0;
	while (i < vars()->nb_philos)
	{
		if (check_locked(i))
		{
			pthread_mutex_unlock(&vars()->forks[i]);
			pthread_mutex_unlock(&vars()->eat[i]);
		}
		i++;
	}
}
