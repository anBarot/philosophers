/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/05/18 12:07:23 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define S_FORK			"has taken a fork\n"
# define S_EAT			"is eating\n"
# define S_SLEEP		"is sleeping\n"
# define S_THINK		"is thinking\n"
# define S_DIE			"died\n"
# define S_REACHED		"has eaten his last meal\n"
# define S_ERR_MUTEX	"Error : can't create mutex\n"
# define S_ERR_THREAD	"Error : can't create thread\n"
# define S_ERR_ARG		"Error : wrong arguments\n"
# define S_STR_TEMPL	"________ <    > "

enum				e_enum
{
	SUCCESS,
	ARG_ERROR,
	MUTEX_ERROR,
	THREAD_ERROR,
	MEAL_NB_REACHED,
};

typedef struct		s_thread
{
	pthread_t		tid;
	int				phi_nb;
	int				meal_nb;
	int				last_time_eat;
	pthread_mutex_t	read_time_mutex;
	pthread_t		monitor_tid;
}					t_thread;

typedef struct		s_philo
{
	int				philo_nb;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	int				meal_lim;
	int				nb_finished_threads;
	bool			is_limited_meal;
	bool			get_started;
	bool			dead;
	int				nb_eaten;
	char			*to_display;
	t_thread		*philo_threads;
	pthread_mutex_t	display_mutex;
	pthread_mutex_t	taking_fork_mutex;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	finished_meal_mutex;
}					t_philo;

t_philo g_phi;
struct timeval g_startime;

int					ft_atoi(char *str);
int					ft_strlen(char *str);
void				*ft_calloc(int size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				display_act(int nb, char *action, t_thread *philo, int time);
int					get_timelaps();
int					ft_init_threads();
int					ft_set_gphilo(void);
void				ft_set_philothreads(t_thread *philo_threads);
void				*philo_routine();
int					ft_init_monitor(t_thread *philo);
void				*monitor_routine();

#endif
