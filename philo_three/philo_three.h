/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 19:18:48 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 17:02:31 by abarot           ###   ########.fr       */
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
# define S_STR_TEMPL	"________ <    > "

enum				e_enum
{
	SUCCESS,
	ARG_ERROR,
	PROC_ERROR,
	THREAD_ERROR,
};

typedef struct		s_sem
{
	sem_t			*display;
	sem_t			*takef;
	sem_t			*forks;
	sem_t			*end_program;
	sem_t			*finished_meal;
}					t_sem;

typedef struct		s_time
{
	int				die;
	int				eat;
	int				sleep;
}					t_time;

typedef struct		s_eat
{
	bool			is_limited_meal;
	int				meal_nb;
	int				meal_lim;
}					t_eat;

typedef struct		s_philo
{
	int				last_time_eat;
	bool			dead;
	int				number;
	int				id;
	char			*to_display;
	pid_t			*pid;
	t_eat			eat_info;
	pthread_t		monitor_tid;
	pthread_t		eating_routine;
	t_time			time_to;
	t_sem			sem;
}					t_philo;

t_philo	g_philo;
struct timeval	g_startime;

void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_atoi(char *str);
int					ft_strlen(char *str);
void				*ft_calloc(int size);
void				display_act(int nb, char *action);
int					get_timelaps();
int					ft_init_process();
int					ft_set_gphilo(void);
void				ft_philo_routine();
int					ft_init_monitor();
void				*monitor_routine();
void				*meal_count_routine();
void				clear_philo();

#endif
