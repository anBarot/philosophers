/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 18:20:18 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <semaphore.h>
# define S_FORK			"has taken a fork\n"
# define S_EAT			"is eating\n"
# define S_SLEEP		"is sleeping\n"
# define S_THINK		"is thinking\n"
# define S_DIE			"died\n"
# define S_REACHED		"has eaten his last meal\n"
# define S_ERR_SEM		"Error : can't create semaphore\n"
# define S_ERR_THREAD	"Error : can't create thread\n"
# define S_ERR_ARG		"Error : wrong arguments\n"

enum				e_enum
{
	SUCCESS,
	ARG_ERROR,
	SEM_ERROR,
	THREAD_ERROR,
};

typedef struct		s_thread
{
	pthread_t		tid;
	int				phi_nb;
	int				meal_nb;
	int				last_time_eat;
	pthread_t		monitor_tid;
}					t_thread;

typedef struct		s_philo
{
	int				philo_nb;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				meal_lim;
	int				nb_finished_threads;
	bool			is_limited_meal;
	bool			dead;
	t_thread		*philo_threads;
	sem_t			*display_sem;
	sem_t			*takef_sem;
	sem_t			*forks_sem;
	sem_t			*finished_meal_sem;
}					t_philo;

t_philo g_phi;
struct timeval g_startime;

void				ft_looptoa(int nbr, char *res, char *base);
int					ft_atoi(char *str);
char				*ft_itoa(int nbr);
int					ft_strlen(char *str);
void				*ft_calloc(int size);
void				display_act(int nb, char *action);
int					ft_get_timelaps();
int					ft_init_threads();
void				ft_set_philothreads(t_thread *philo_threads);
int					ft_set_gphilo(void);
void				*philo_routine();
int					ft_init_monitor(t_thread *philo);
void				*monitor_routine(void *arg);

#endif
