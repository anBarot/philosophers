/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/03/03 17:32:02 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*monitor_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_philo.is_dead == false)
	{
		if ((ft_get_timelaps() - philo->last_time_eat) > g_philo.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			sem_wait(g_philo.display_sem);
			g_philo.is_dead = true;
		}
		if (g_philo.is_limited_meal == true && philo->meal_nb == g_philo.meal_limit)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			sem_wait(g_philo.finished_meal_sem);
			g_philo.nb_finished_threads = g_philo.nb_finished_threads + 1;
			sem_post(g_philo.finished_meal_sem);
			return (NULL);
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	sem_wait(g_philo.takef_sem);
	sem_wait(g_philo.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	sem_wait(g_philo.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	sem_post(g_philo.takef_sem);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_philo.forks_sem);
	sem_post(g_philo.forks_sem);
}

void	*philo_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	if (ft_init_monitor(philo))
		return ((void *)THREAD_ERROR);
	while (1)
	{
		ft_eating_routine(philo);
		if (g_philo.is_limited_meal == true && philo->meal_nb == g_philo.meal_limit)
		{
			return (NULL);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_philo.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
	}
	return (NULL);
}
