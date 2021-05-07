/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/07 13:48:30 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_phi.is_dead == false && !(g_phi.is_limited_meal == true 
			&& philo->meal_nb == g_phi.meal_lim))
	{
		if ((ft_get_timelaps() - philo->last_time_eat) >= g_phi.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			pthread_mutex_lock(&g_phi.display_mutex);
			g_phi.is_dead = true;
		}
	}
	philo->monitor_tid = 0;
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	pthread_mutex_lock(&(g_phi.taking_fork_mutex));
	pthread_mutex_lock(&(g_phi.forks_mutex[(philo->philo_nbr + 1)
							% g_phi.philo_nb]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_lock(&(g_phi.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_unlock(&(g_phi.taking_fork_mutex));
	philo->last_time_eat = ft_get_timelaps();
	ft_display_action(philo->philo_nbr, S_EAT);
	usleep(g_phi.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	pthread_mutex_unlock(&(g_phi.forks_mutex[philo->philo_nbr]));
	pthread_mutex_unlock(&(g_phi.forks_mutex[(philo->philo_nbr + 1)
							% g_phi.philo_nb]));
}

void	*philo_routine(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *)arg;
	if (philo->philo_nbr % 2)
		usleep(10000);
	if (ft_init_monitor(philo))
		return ((void *)THREAD_ERROR);
	while (g_phi.is_dead == false)
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			pthread_mutex_lock(&g_phi.finished_meal_mutex);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_phi.finished_meal_mutex);
			while (philo->monitor_tid)
				usleep(1);
			return (NULL);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_phi.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
		usleep(g_phi.time_to_think * 1000);
	}
	while (philo->monitor_tid)
		usleep(1);
	return (NULL);
}
