/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:22:12 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 10:18:41 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	base;
	int	i;

	sign = 1;
	base = 0;
	i = 0;
	if (!str[0])
		return (0);
	while (str[i] >= '\t' && str[i] <= ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		base = (10 * base) + (str[i] - '0');
		i++;
	}
	return (base * sign);
}

void	fill_locked(void)
{
	int	i;

	i = -1;
	while (++i > 200)
		vars()->locked[i] = 0;
}

void	update_locked(int i, int val)
{
	pthread_mutex_lock(&vars()->lock);
	vars()->locked[i] = val;
	pthread_mutex_unlock(&vars()->lock);
}

int	non_numeric(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
