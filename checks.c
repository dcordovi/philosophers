/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:58:10 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 11:08:15 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_alive(void)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&vars()->alive);
	ret = vars()->all_alive;
	pthread_mutex_unlock(&vars()->alive);
	return (ret);
}

int	check_all_starve(void)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&vars()->starve);
	ret = vars()->all_starve;
	pthread_mutex_unlock(&vars()->starve);
	return (ret);
}

int	check_locked(int i)
{
	int	ret;

	pthread_mutex_lock(&vars()->lock);
	ret = vars()->locked[i];
	pthread_mutex_unlock(&vars()->lock);
	return (ret);
}

void	lock_print(uint64_t time, int philo, char *str)
{
	pthread_mutex_lock(&vars()->print);
	printf("%lu %d %s\n", time, philo, str);
	pthread_mutex_unlock(&vars()->print);
}

int	one_philo(int time_die)
{
	printf("0 1 has taken a fork\n");
	printf("%d 1 died\n", time_die);
	return (1);
}
