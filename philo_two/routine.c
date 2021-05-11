/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 18:20:18 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_phi.dead == false && !(g_phi.is_limited_meal == true &&
			philo->meal_nb == g_phi.meal_lim))
	{
		if ((ft_get_timelaps() - philo->last_time_eat) >= g_phi.tt_die)
		{
			display_act(philo->phi_nb, S_DIE);
			sem_wait(g_phi.display_sem);
			g_phi.dead = true;
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	sem_wait(g_phi.takef_sem);
	sem_wait(g_phi.forks_sem);
	display_act(philo->phi_nb, S_FORK);
	sem_wait(g_phi.forks_sem);
	display_act(philo->phi_nb, S_FORK);
	sem_post(g_phi.takef_sem);
	display_act(philo->phi_nb, S_EAT);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_phi.tt_eat * 1000);
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
	while (g_phi.dead == false && !(g_phi.is_limited_meal == true &&
			philo->meal_nb == g_phi.meal_lim))
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true &&
				philo->meal_nb == g_phi.meal_lim)
		{
			display_act(philo->phi_nb, S_REACHED);
			sem_wait(g_phi.finished_meal_sem);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			sem_post(g_phi.finished_meal_sem);
			return (NULL);
		}
		display_act(philo->phi_nb, S_SLEEP);
		usleep(g_phi.tt_sleep * 1000);
		display_act(philo->phi_nb, S_THINK);
	}
	return (NULL);
}
