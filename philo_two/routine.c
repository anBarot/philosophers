/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 12:14:42 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor_routine(t_thread *philo)
{
	int		time;

	while (g_phi.dead == false)
	{
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
			break ;
		sem_wait(g_phi.finished_meal_sem);
		time = get_timelaps();
		if ((time - philo->last_time_eat) >= g_phi.tt_die)
		{
			g_phi.dead = true;
			display_act(philo->phi_nb + 1, S_DIE);
			sem_post(g_phi.finished_meal_sem);
			return (NULL);
		}
		sem_post(g_phi.finished_meal_sem);
		usleep(1000);
	}
	return (NULL);
}

void	eating_routine(t_thread *philo)
{
	sem_wait(g_phi.takef_sem);
	sem_wait(g_phi.forks_sem);
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK) : 0;
	sem_wait(g_phi.forks_sem);
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK) : 0;
	sem_post(g_phi.takef_sem);
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_EAT) : 0;
	sem_wait(g_phi.finished_meal_sem);
	philo->last_time_eat = get_timelaps();
	sem_post(g_phi.finished_meal_sem);
	usleep(g_phi.tt_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_phi.forks_sem);
	sem_post(g_phi.forks_sem);
}

void	*philo_routine(t_thread *philo)
{
	philo->last_time_eat = get_timelaps();
	if (ft_init_monitor(philo))
		return ((void *)THREAD_ERROR);
	while (g_phi.dead == false)
	{
		eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_REACHED) : 0;
			sem_wait(g_phi.finished_meal_sem);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			sem_post(g_phi.finished_meal_sem);
			return (NULL);
		}
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_SLEEP) : 0;
		usleep(g_phi.tt_sleep * 1000);
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_THINK) : 0;
	}
	return (NULL);
}
