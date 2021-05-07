/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/07 14:28:27 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_phi.is_dead == false && !(g_phi.is_limited_meal == true &&
			philo->meal_nb == g_phi.meal_lim))
	{
		if ((ft_get_timelaps() - philo->last_time_eat) >= g_phi.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			sem_wait(g_phi.display_sem);
			g_phi.is_dead = true;
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	sem_wait(g_phi.takef_sem);
	sem_wait(g_phi.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	sem_wait(g_phi.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	sem_post(g_phi.takef_sem);
	ft_display_action(philo->philo_nbr, S_EAT);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_phi.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_phi.forks_sem);
	sem_post(g_phi.forks_sem);
}

void	*philo_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	if (ft_init_monitor(philo))
		return ((void *)THREAD_ERROR);
	while (g_phi.is_dead == false && !(g_phi.is_limited_meal == true &&
			philo->meal_nb == g_phi.meal_lim))
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true &&
				philo->meal_nb == g_phi.meal_lim)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			sem_wait(g_phi.finished_meal_sem);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			sem_post(g_phi.finished_meal_sem);
			return (NULL);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_phi.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
	}
	return (NULL);
}
