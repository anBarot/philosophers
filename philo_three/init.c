/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/03/06 08:55:50 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_set_gphilo(char **av)
{
	int i;

	i = 0;
	if ((g_philo.philo_nb = ft_atoi(av[1])) < 2 ||
		(g_philo.time_to_die = ft_atoi(av[2])) < 0 ||
		(g_philo.time_to_eat = ft_atoi(av[3])) < 0 ||
		(g_philo.time_to_sleep = ft_atoi(av[4])) < 0 ||
		!(g_philo.forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, g_philo.philo_nb)) ||
		!(g_philo.takef_sem = sem_open("takef_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.display_sem = sem_open("display_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.finished_meal_sem = sem_open("finished_meal_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.pid = malloc(sizeof(pid_t) * g_philo.philo_nb))
		)
		return (EXIT_FAILURE);
	g_philo.is_dead = false;
	if (av[5])
	{
		g_philo.is_limited_meal = true;
		if ((g_philo.meal_limit = ft_atoi(av[5])) < 0)
			return (EXIT_FAILURE);
	}
	else
		g_philo.is_limited_meal = false;
	return (EXIT_SUCCESS);
}

int ft_init_proc()
{
	t_proc *philo_proc;
	int i;

	i = 0;
	if (!(philo_proc = malloc(sizeof(t_proc) * g_philo.philo_nb)))
		return (EXIT_FAILURE);
	while (i < g_philo.philo_nb)
	{
		philo_proc[i].philo_nbr = i;
		philo_proc[i].meal_nb = 0;
		if (!(g_philo.pid[i] = fork()))
		{
			ft_philo_routine(&(philo_proc[i]));
			exit(EXIT_SUCCESS);
		}
		else
			i++;
	}
	while (i >= 0)
	{
		waitpid(g_philo.pid[i], &philo_proc[i].status, 0);
		i--;
	}
	return (EXIT_SUCCESS);
}

int		ft_init_monitor(t_proc *philo)
{
	int err;

	err = 0;
	if ((err = pthread_create(&(philo->monitor_tid), NULL, ft_monitor_routine, philo)))
	{
		write(1, S_ERR_thread, ft_strlen(S_ERR_thread));
		return (err);
	}
	pthread_detach(philo->monitor_tid);
	return (err);
}