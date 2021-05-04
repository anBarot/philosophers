/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/05/04 14:50:32 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_set_gphilo(void)
{
	int i;

	i = 0;
	if (!(g_philo.forks_mutex = malloc(sizeof(pthread_mutex_t)
										* g_philo.philo_nb)) ||
		(pthread_mutex_init(&g_philo.taking_fork_mutex, NULL)) ||
		(pthread_mutex_init(&g_philo.display_mutex, NULL)) ||
		(pthread_mutex_init(&g_philo.finished_meal_mutex, NULL)))
	{
		write(1, S_ERR_MUTEX, ft_strlen(S_ERR_MUTEX));
		return (MUTEX_ERROR);
	}
	while (i < g_philo.philo_nb)
	{
		if ((pthread_mutex_init(&g_philo.forks_mutex[i], NULL)))
		{
			write(1, S_ERR_MUTEX, ft_strlen(S_ERR_MUTEX));
			return (MUTEX_ERROR);
		}
		i++;
	}
	g_philo.is_dead = false;
	g_philo.nb_finished_threads = 0;
	g_philo.nb_eaten = 0;
	return (SUCCESS);
}

int		ft_init_threads(void)
{
	int			i;
	int			err;

	i = 0;
	if (!(g_philo.philo_threads = malloc(sizeof(t_thread) * g_philo.philo_nb)))
		return (EXIT_FAILURE);
	gettimeofday(&g_startime, NULL);
	while (i < g_philo.philo_nb)
	{
		g_philo.philo_threads[i].philo_nbr = i;
		g_philo.philo_threads[i].meal_nb = 0;
		if ((err = pthread_create(&(g_philo.philo_threads[i].tid), NULL,
				philo_routine, &(g_philo.philo_threads[i]))))
		{
			write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
			return (THREAD_ERROR);
		}
		pthread_detach(g_philo.philo_threads[i].tid);
		i++;
	}
	return (SUCCESS);
}

int		ft_init_monitor(t_thread *philo)
{
	int err;

	err = 0;
	pthread_mutex_init(&philo->monitor_mutex, NULL);
	if ((err = pthread_create(&(philo->monitor_tid), NULL,
			monitor_routine, philo)))
	{
		write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
		return (err);
	}
	pthread_detach(philo->monitor_tid);
	return (err);
}
