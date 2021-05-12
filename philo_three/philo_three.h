/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 12:12:13 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
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
	PROC_ERROR,
	THREAD_ERROR,
};

typedef struct		s_proc
{
	int				status;
	bool			dead;
	int				phi_nb;
	int				meal_nb;
	int				last_time_eat;
	pthread_t		monitor_tid;
}					t_proc;

typedef struct		s_philo
{
	t_proc			*philo_proc;
	pid_t			*pid;
	pthread_t		eating_monitor;
	int				philo_nb;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				meal_lim;
	bool			is_limited_meal;
	sem_t			*display_sem;
	sem_t			*takef_sem;
	sem_t			*forks_sem;
	sem_t			*end_program_sem;
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
int					get_timelaps();
int					ft_init_proc();
void				ft_set_philothreads(t_proc *philo_threads);
int					ft_set_gphilo(void);
void				ft_philo_routine(t_proc *philo);
int					ft_init_monitor(t_proc *philo);
void				*ft_monitor_routine(void *arg);
void				clear_philo(void);

#endif
