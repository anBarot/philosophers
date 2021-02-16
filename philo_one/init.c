/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/02/16 18:53:53 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_set_gphilo(char **av)
{
	int i;

	i = 0;
	if ((g_philo.philo_nb = ft_atoi(av[1])) < 2 ||
		(g_philo.time_to_die = ft_atoi(av[2])) < 0 ||
		(g_philo.time_to_eat = ft_atoi(av[3])) < 0 ||
		(g_philo.time_to_sleep = ft_atoi(av[4])) < 0 ||
		!(g_philo.forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_philo.philo_nb)) ||
		(pthread_mutex_init(&g_philo.display_mutex, NULL)) ||
		(pthread_mutex_init(&g_death_monitor.monitor_mutex, NULL)))
		return (EXIT_FAILURE);
	while (i < g_philo.philo_nb)
	{
		if ((pthread_mutex_init(&g_philo.forks_mutex[i], NULL)))
			return (EXIT_FAILURE);
		i++;
	}
	g_philo.ending = false;
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
