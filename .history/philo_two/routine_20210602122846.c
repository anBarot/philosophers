/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/06/02 12:28:46 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*monitor_routine(void)
{
	int	i;

	while (g_phi.get_started == false)
		;
	while (g_phi.dead == false)
	{
		if (g_phi.is_limited_meal == true && g_phi.philo_nb == g_phi.nb_finished_threads)
			break ;
		i = 0;
		while (i < g_phi.philo_nb)
		{
			sem_wait(g_phi.read_time_sem);
			if ((get_time() - g_phi.philo_threads[i].last_time_eat) >= g_phi.tt_die)
			{
				g_phi.dead = true;
				sem_post(g_phi.read_time_sem);
				display_act(i + 1, S_DIE);
				return (NULL);
			}
			sem_post(g_phi.read_time_sem);
			i++;
			usleep(1000);
		}
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
	sem_wait(g_phi.read_time_sem);
	philo->last_time_eat = get_timelaps();
	sem_post(g_phi.read_time_sem);
	ft_usleep(g_phi.tt_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_phi.forks_sem);
	sem_post(g_phi.forks_sem);
}

void	*philo_routine(t_thread *philo)
{
	while(g_phi.get_started == false)
		;
	(philo->phi_nb % 2) ? usleep(1000) : 0;
	if (g_phi.philo_nb % 2 == 1 && philo->phi_nb == g_phi.philo_nb - 1)
		usleep(2000);
	while (g_phi.dead == false)
	{
		eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			(g_phi.dead == false) ? display_act(philo->phi_nb + 1,
												S_REACHED) : 0;
			sem_wait(g_phi.finished_meal_sem);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			sem_post(g_phi.finished_meal_sem);
			return (NULL);
		}
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_SLEEP) : 0;
		ft_usleep(g_phi.tt_sleep * 1000);
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_THINK) : 0;
		(g_phi.philo_nb % 2 == 1) ? usleep(g_phi.tt_think * 1000) : 0;
	}
	return (NULL);
}
