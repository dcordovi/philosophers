/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:23:27 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 10:03:45 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_vars	*vars(void)
{
	static t_vars	var;

	return (&var);
}

void	handle_forks_and_eat(t_philo *philo)
{
	if (check_all_alive())
		lock_print(time_after(), philo->i + 1, "has taken a fork");
	if (check_all_alive())
		lock_print(time_after(), philo->i + 1, "has taken a fork");
	pthread_mutex_lock(&vars()->eat[philo->i]);
	philo->times_eaten++;
	vars()->philos[philo->i].last_eat = time_after();
	pthread_mutex_unlock(&vars()->eat[philo->i]);
	if (check_all_alive())
		lock_print(get_time() - vars()->start_time, philo->i + 1, "is eating");
	ft_usleep(vars()->time_eat);
	update_locked(philo->i, 0);
	update_locked((philo->i + 1) % vars()->nb_philos, 0);
}

void	eat(t_philo *philo)
{
	int	left_fork;
	int	right_fork;
	int	temp;

	right_fork = (philo->i + 1) % vars()->nb_philos;
	left_fork = philo->i;
	if (left_fork > right_fork)
	{
		temp = left_fork;
		left_fork = right_fork;
		right_fork = temp;
	}
	pthread_mutex_lock(&vars()->forks[left_fork]);
	pthread_mutex_lock(&vars()->forks[right_fork]);
	handle_forks_and_eat(philo);
	pthread_mutex_unlock(&vars()->forks[left_fork]);
	pthread_mutex_unlock(&vars()->forks[right_fork]);
}

void	sleep_philo(t_philo *philo)
{
	lock_print(get_time() - vars()->start_time, philo->i + 1, "is sleeping");
	ft_usleep(vars()->time_sleep);
}

void	think(t_philo *philo)
{
	lock_print(time_after(), philo->i + 1, "is thinking");
}
