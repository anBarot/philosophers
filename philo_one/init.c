/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 16:50:01 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_set_gphilo(void)
{
	int i;

	i = 0;
	if (!(g_phi.forks_mutex = malloc(sizeof(pthread_mutex_t)
										* g_phi.philo_nb)) ||
		(pthread_mutex_init(&g_phi.taking_fork_mutex, NULL)) ||
		(pthread_mutex_init(&g_phi.display_mutex, NULL)) ||
		(pthread_mutex_init(&g_phi.finished_meal_mutex, NULL)))
	{
		write(1, S_ERR_MUTEX, ft_strlen(S_ERR_MUTEX));
		return (MUTEX_ERROR);
	}
	while (i < g_phi.philo_nb)
	{
		if ((pthread_mutex_init(&g_phi.forks_mutex[i], NULL)))
		{
			write(1, S_ERR_MUTEX, ft_strlen(S_ERR_MUTEX));
			return (MUTEX_ERROR);
		}
		i++;
	}
	g_phi.dead = false;
	g_phi.nb_finished_threads = 0;
	g_phi.nb_eaten = 0;
	return (SUCCESS);
}

int		ft_init_threads(void)
{
	int			i;
	int			err;

	i = 0;
	if (!(g_phi.philo_threads = malloc(sizeof(t_thread) * g_phi.philo_nb)))
		return (EXIT_FAILURE);
	gettimeofday(&g_startime, NULL);
	while (i < g_phi.philo_nb)
	{
		pthread_mutex_init(&(g_phi.philo_threads[i].read_time_mutex), NULL);
		g_phi.philo_threads[i].phi_nb = i;
		g_phi.philo_threads[i].meal_nb = 0;
		if ((err = pthread_create(&(g_phi.philo_threads[i].tid), NULL,
				philo_routine, &(g_phi.philo_threads[i]))))
		{
			write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
			return (THREAD_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int		ft_init_monitor(t_thread *philo)
{
	int err;

	err = 0;
	if ((err = pthread_create(&(philo->monitor_tid), NULL,
			monitor_routine, philo)))
	{
		write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
		return (err);
	}
	pthread_detach(philo->monitor_tid);
	return (err);
}
