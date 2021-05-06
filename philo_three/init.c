/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/05/06 19:52:47 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*eating_monitor(void *count)
{
	int *counter;

	counter = (int *)count;
	while (*counter)
	{
		sem_wait(g_phi.finished_meal_sem);
		*counter = *counter - 1;
	}
	sem_post(g_phi.end_program_sem);
	return (NULL);
}

int		ft_set_gphilo(void)
{
	int i;

	i = 0;
	if ((!(g_phi.forks_sem =
		sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, g_phi.philo_nb)) ||
		!(g_phi.takef_sem =
		sem_open("takef_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.display_sem =
		sem_open("display_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.end_program_sem =
		sem_open("end_program_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.finished_meal_sem =
		sem_open("finished_meal_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_phi.pid = malloc(sizeof(pid_t) * g_phi.philo_nb))))
		return (EXIT_FAILURE);
	g_phi.is_dead = false;
	return (EXIT_SUCCESS);
}

int		ft_init_proc(void)
{
	t_proc	*philo_proc;
	int		i;
	int		err;

	i = 0;
	sem_wait(g_phi.end_program_sem);
	if (!(philo_proc = malloc(sizeof(t_proc) * g_phi.philo_nb)))
		return (EXIT_FAILURE);
	while (i < g_phi.philo_nb)
	{
		philo_proc[i].philo_nbr = i;
		philo_proc[i].meal_nb = 0;
		if ((g_phi.pid[i] = fork()) == -1)
			return (EXIT_FAILURE);
		else if (!g_phi.pid[i])
		{
			ft_philo_routine(&(philo_proc[i]));
			sem_post(g_phi.finished_meal_sem);
			while(1);
		}
		i++;
	}
	if (g_phi.is_limited_meal == true)
	{
		if ((err = pthread_create(&(g_phi.eating_monitor), NULL,
					eating_monitor, &g_phi.philo_nb)))
		{
			write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
			return (err);
		}
		pthread_detach(g_phi.eating_monitor);
	}
	return (EXIT_SUCCESS);
}

int		ft_init_monitor(t_proc *philo)
{
	int err;

	if ((err = pthread_create(&(philo->monitor_tid), NULL,
				ft_monitor_routine, philo)))
	{
		write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
		return (err);
	}
	pthread_detach(philo->monitor_tid);
	return (err);
}
