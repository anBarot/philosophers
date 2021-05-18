/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/18 12:19:08 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(t_thread *philo)
{
	int time;

	while (g_phi.dead == false)
	{
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
			break ;
		time = get_timelaps();
		pthread_mutex_lock(&(philo->read_time_mutex));
		if ((time - philo->last_time_eat) >= g_phi.tt_die)
		{
			g_phi.dead = true;
			pthread_mutex_unlock(&(philo->read_time_mutex));
			display_act(philo->phi_nb + 1, S_DIE, philo, get_timelaps());
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->read_time_mutex));
	}
	return (NULL);
}

void	taking_forks(t_thread *philo)
{
	(philo->phi_nb % 2) ? pthread_mutex_lock(
		&(g_phi.forks_mutex[(philo->phi_nb + 1) % g_phi.philo_nb])) :
		pthread_mutex_lock(&(g_phi.forks_mutex[philo->phi_nb]));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK, philo, get_timelaps()) : 0;
	(philo->phi_nb % 2) ? pthread_mutex_lock(
		&(g_phi.forks_mutex[philo->phi_nb])) : pthread_mutex_lock(
		&(g_phi.forks_mutex[(philo->phi_nb + 1) % g_phi.philo_nb]));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK, philo, get_timelaps()) : 0;
}

void	eating_routine(t_thread *philo)
{
	int	time;

	taking_forks(philo);
	time = get_timelaps();
	pthread_mutex_lock(&(philo->read_time_mutex));
	philo->last_time_eat = time;
	pthread_mutex_unlock(&(philo->read_time_mutex));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_EAT, philo, time) : 0;
	usleep(g_phi.tt_eat * 1000);
	pthread_mutex_unlock(&(g_phi.forks_mutex[philo->phi_nb]));
	pthread_mutex_unlock(&(g_phi.forks_mutex[(philo->phi_nb + 1)
							% g_phi.philo_nb]));
	philo->meal_nb = philo->meal_nb + 1;
}

void	*philo_routine(t_thread *philo)
{
	while(g_phi.get_started == false)
		;
	philo->last_time_eat = get_timelaps();
	ft_init_monitor(philo);
	(philo->phi_nb % 2) ? usleep(1000) : 0;
	while (g_phi.dead == false)
	{
		eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			(g_phi.dead == false) ? display_act(philo->phi_nb, S_REACHED, philo, get_timelaps()) : 0;
			pthread_mutex_lock(&g_phi.finished_meal_mutex);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_phi.finished_meal_mutex);
			return (NULL);
		}
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_SLEEP, philo, get_timelaps()) : 0;
		usleep(g_phi.tt_sleep * 1000);
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_THINK, philo, get_timelaps()) : 0;
		usleep(1000);
	}
	return (NULL);
}
