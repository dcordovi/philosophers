/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:21:26 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/05 12:56:33 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	time_after(void)
{
	return (get_time() - vars()->start_time);
}

int	ft_usleep(useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time && check_all_alive())
		usleep(time / 10);
	return (0);
}
