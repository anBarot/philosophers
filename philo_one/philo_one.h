/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/02/16 18:52:43 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#define S_FORK			"has taken a fork"
#define S_EAT			"is eating"
#define S_SLEEP			"is sleeping"
#define S_THINK			"is thinking"
#define S_DIE			"died"
#define S_ERR_thread	"\nError : can't create thread\n"
#define t_timeval		struct timeval

enum	e_action_nb
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
};

typedef struct		s_philo
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	bool			is_limited_meal;
	bool			ending;
	pthread_mutex_t	display_mutex;
	pthread_mutex_t	*forks_mutex;
}					t_philo;

typedef struct		s_thread
{
	pthread_t 		tid;
	int				philo_nbr;
	int				meal_nb;
}					t_thread;

typedef struct		s_death_monitor
{
	pthread_t 		tid;
	pthread_mutex_t	monitor_mutex;
	int				last_time_eat;
}					t_death_monitor;

t_philo g_philo;
t_timeval g_startime;

void	ft_looptoa(int nbr, char *res, char *base);
int		ft_atoi(char *str);
char	*ft_itoa(int nbr);
int		ft_strlen(char *str);
void	*ft_calloc(int size);
void	ft_display_action(int nb, char *action);
int		ft_get_timelaps();
int		ft_init_threads();
void	ft_set_philothreads(t_thread *philo_threads);
int		ft_set_gphilo(char **av);
void	*philo_routine();
void	*death_monitor_routine(void *arg);

#endif
