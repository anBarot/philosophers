/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/02/17 11:44:05 by abarot           ###   ########.fr       */
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

#define S_FORK			"has taken a fork\n"
#define S_EAT			"is eating\n"
#define S_SLEEP			"is sleeping\n"
#define S_THINK			"is thinking\n"
#define S_DIE			"died\n"
#define S_REACHED		"has eaten his last meal\n"
#define S_ERR_thread	"\nError : can't create thread\n"
#define t_timeval		struct timeval
#define ARG_ERROR		1
#define THREAD_ERROR	2
#define MEAL_NB_REACHED	3

typedef struct		s_philo
{
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_limit;
	int				nb_finished_threads;
	bool			is_limited_meal;
	bool			is_dead;
	pthread_mutex_t	display_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	finished_meal_mutex;
}					t_philo;

typedef struct		s_thread
{
	pthread_t 		tid;
	int				philo_nbr;
	int				meal_nb;
	int				last_time_eat;
	pthread_t 		monitor_tid;
	pthread_mutex_t	monitor_mutex;
}					t_thread;

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
int		ft_init_monitor(t_thread *philo);
void	*monitor_routine(void *arg);

#endif
