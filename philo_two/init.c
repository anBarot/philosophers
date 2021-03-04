/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/03/03 17:21:30 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		!(g_philo.finished_meal_sem = sem_open("finished_meal_sem", O_CREAT | O_EXCL, S_IRWXU, 1))
		)
		return (EXIT_FAILURE);
	g_philo.is_dead = false;
	g_philo.nb_finished_threads = 0;
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

int ft_init_threads()
{
	t_thread *philo_threads;
	int i;
	int err;

	i = 0;
	if (!(philo_threads = malloc(sizeof(t_thread) * g_philo.philo_nb)))
		return (EXIT_FAILURE);
	while (i < g_philo.philo_nb)
	{
		philo_threads[i].philo_nbr = i;
		philo_threads[i].meal_nb = 0;
		if ((err = pthread_create(&(philo_threads[i].tid), NULL, philo_routine, &(philo_threads[i]))))
		{
			write(1, S_ERR_thread, ft_strlen(S_ERR_thread));
			return (EXIT_FAILURE);
		}
		pthread_detach(philo_threads[i].tid);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		ft_init_monitor(t_thread *philo)
{
	int err;

	err = 0;
	if ((err = pthread_create(&(philo->monitor_tid), NULL, monitor_routine, philo)))
	{
		write(1, S_ERR_thread, ft_strlen(S_ERR_thread));
		return (err);
	}
	pthread_detach(philo->monitor_tid);
	return (err);
}