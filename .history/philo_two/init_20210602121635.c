/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/06/02 12:16:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_set_gphilo(void)
{
	int i;

	i = 0;
	if (!(g_phi.forks_sem =
		sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, g_phi.philo_nb)) ||
		!(g_phi.takef_sem =
		sem_open("takef_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.display_sem =
		sem_open("display_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.finished_meal_sem =
		sem_open("finished_meal_sem", O_CREAT | O_EXCL, S_IRWXU, 1)))
	{
		write(1, S_ERR_SEM, ft_strlen(S_ERR_SEM));
		return (SEM_ERROR);
	}
	g_phi.dead = false;
	g_phi.nb_finished_threads = 0;
	return (SUCCESS);
}

int		ft_init_threads(void)
{
	int			i;
	int			err;

	i = 0;
	if (!(g_phi.philo_threads = malloc(sizeof(t_thread) * g_phi.philo_nb)))
		return (EXIT_FAILURE);
	g_phi.get_started = false;
	ft_init_monitor();
	while (i < g_phi.philo_nb)
	{
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
	gettimeofday(&g_startime, NULL);
	g_phi.get_started = true;
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
		return (THREAD_ERROR);
	}
	pthread_detach(philo->monitor_tid);
	return (SUCCESS);
}
