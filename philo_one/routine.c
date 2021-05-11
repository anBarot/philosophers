/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 13:04:17 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(void)
{
	int		i;

	while (g_phi.is_dead == false)
	{
		i = 0;
		while (i < g_phi.philo_nb)
		{
			if ((ft_get_timelaps() - g_phi.philo_threads[i].last_time_eat) >= g_phi.time_to_die)
			{
				ft_display_action(g_phi.philo_threads[i].philo_nbr + 1, S_DIE);
				pthread_mutex_lock(&g_phi.display_mutex);
				g_phi.is_dead = true;
			}
			i++;
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_thread *philo)
{
	// pthread_mutex_lock(&(g_phi.taking_fork_mutex));
	pthread_mutex_lock(&(g_phi.forks_mutex[(philo->philo_nbr + 1)
							% g_phi.philo_nb]));
	ft_display_action(philo->philo_nbr + 1, S_FORK);
	pthread_mutex_lock(&(g_phi.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr + 1, S_FORK);
	// pthread_mutex_unlock(&(g_phi.taking_fork_mutex));
	philo->last_time_eat = ft_get_timelaps();
	ft_display_action(philo->philo_nbr + 1, S_EAT);
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
	philo->last_time_eat = ft_get_timelaps();
	while (g_phi.is_dead == false)
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			pthread_mutex_lock(&g_phi.finished_meal_mutex);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_phi.finished_meal_mutex);
			return (NULL);
		}
		ft_display_action(philo->philo_nbr + 1, S_SLEEP);
		usleep(g_phi.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr + 1, S_THINK);
	}
	return (NULL);
}
