/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 14:32:21 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(void)
{
	int	i;

	i = 0;
	while (g_phi.is_dead == false)
	{
		i = 0;
		while (i < g_phi.philo_nb)
		{
			pthread_mutex_lock(&(g_phi.philo_threads[i].read_time_mutex));
			if ((ft_get_timelaps() - g_phi.philo_threads[i].last_time_eat) >= g_phi.time_to_die)
			{
				g_phi.is_dead = true;
				ft_display_action(g_phi.philo_threads[i].philo_nbr + 1, S_DIE);
				pthread_mutex_unlock(&(g_phi.philo_threads[i].read_time_mutex));
			}
			pthread_mutex_unlock(&(g_phi.philo_threads[i].read_time_mutex));
			i++;
			usleep(500);
		}
		usleep(500);
	}
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	pthread_mutex_lock(&(g_phi.taking_fork_mutex));
	pthread_mutex_lock(&(g_phi.forks_mutex[(philo->philo_nbr + 1)
							% g_phi.philo_nb]));
	(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr + 1, S_FORK) : 0;
	pthread_mutex_lock(&(g_phi.forks_mutex[philo->philo_nbr]));
	(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr + 1, S_FORK) : 0;
	pthread_mutex_unlock(&(g_phi.taking_fork_mutex));
	pthread_mutex_lock(&(philo->read_time_mutex));
	philo->last_time_eat = ft_get_timelaps();
	pthread_mutex_unlock(&(philo->read_time_mutex));
	(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr + 1, S_EAT) : 0;
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
	philo->last_time_eat = ft_get_timelaps();
	if (philo->philo_nbr % 2)
		usleep(1000);
	while (g_phi.is_dead == false)
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr, S_REACHED) : 0;
			pthread_mutex_lock(&g_phi.finished_meal_mutex);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_phi.finished_meal_mutex);
			return (NULL);
		}
		(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr + 1, S_SLEEP) : 0;
		usleep(g_phi.time_to_sleep * 1000);
		(g_phi.is_dead == false) ? ft_display_action(philo->philo_nbr + 1, S_THINK) : 0;
	}
	return (NULL);
}
