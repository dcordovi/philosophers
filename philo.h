/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordovi <dcordovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:37:22 by dcordovi          #+#    #+#             */
/*   Updated: 2023/05/10 10:20:39 by dcordovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_philo
{
	char		*status;
	int			i;
	int			times_eaten;
	uint64_t	last_eat;
}	t_philo;

typedef struct s_vars
{
	pthread_mutex_t	forks[200];
	pthread_mutex_t	eat[200];
	pthread_mutex_t	alive;
	pthread_mutex_t	starve;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_t		th[250];
	pthread_t		t_checker;
	t_philo			philos[200];
	int				*arr;
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	uint64_t		start_time;
	int				has_limit;
	int				all_alive;
	int				all_starve;
	int				locked[200];
}	t_vars;

t_vars		*vars(void);
uint64_t	get_time(void);
uint64_t	time_after(void);
int			ft_usleep(useconds_t time);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		eat(t_philo *philo);
void		sleep_philo(t_philo *philo);
void		think(t_philo *philo);
void		initialize_forks(void);
int			create_threads(void);
void		destroy_forks(void);
void		unlock_mutexes(void);
void		assign_vars(int argc, char **argv);
void		*routine(void *args);
void		*checker(void);
int			init_mutexes(void);
int			check_all_alive(void);
int			check_all_starve(void);
int			check_locked(int i);
int			one_philo(int time_die);
void		fill_locked(void);
void		update_locked(int i, int val);
void		handle_forks_and_eat(t_philo *philo);
void		lock_print(uint64_t time, int philo, char *str);
int			non_numeric(int argc, char **argv);
#endif
