/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 19:02:05 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(void)
{
	int		i;
	int		time;

	while (g_phi.dead == false)
	{
		i = 0;
		time = ft_get_timelaps();
		while (i < g_phi.philo_nb)
		{
			pthread_mutex_lock(&(g_phi.read_time_mutex[i]));
			if ((time - g_phi.philo_threads[i].last_time_eat) >= g_phi.tt_die)
			{
				g_phi.dead = true;
				display_act(g_phi.philo_threads[i].phi_nb + 1, S_DIE);
				pthread_mutex_unlock(&(g_phi.read_time_mutex[i]));
				return (NULL);
			}
			pthread_mutex_unlock(&(g_phi.read_time_mutex[i]));
			i++;
		}
	}
	return (NULL);
}

void	ft_taking_forks(t_thread *philo)
{
	pthread_mutex_lock(&(g_phi.taking_fork_mutex));
	pthread_mutex_lock(&(g_phi.forks_mutex[(philo->phi_nb + 1)
							% g_phi.philo_nb]));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK) : 0;
	pthread_mutex_lock(&(g_phi.forks_mutex[philo->phi_nb]));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_FORK) : 0;
	pthread_mutex_unlock(&(g_phi.taking_fork_mutex));
}

void	ft_eating_routine(t_thread *philo)
{
	ft_taking_forks(philo);
	pthread_mutex_lock(&(g_phi.read_time_mutex[philo->phi_nb]));
	philo->last_time_eat = ft_get_timelaps();
	pthread_mutex_unlock(&(g_phi.read_time_mutex[philo->phi_nb]));
	(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_EAT) : 0;
	usleep(g_phi.tt_eat * 1000);
	pthread_mutex_unlock(&(g_phi.forks_mutex[philo->phi_nb]));
	pthread_mutex_unlock(&(g_phi.forks_mutex[(philo->phi_nb + 1)
							% g_phi.philo_nb]));
	philo->meal_nb = philo->meal_nb + 1;
}

void	*philo_routine(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	if (philo->phi_nb % 2)
		usleep(500);
	while (g_phi.dead == false)
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim)
		{
			(g_phi.dead == false) ? display_act(philo->phi_nb, S_REACHED) : 0;
			pthread_mutex_lock(&g_phi.finished_meal_mutex);
			g_phi.nb_finished_threads = g_phi.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_phi.finished_meal_mutex);
			return (NULL);
		}
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_SLEEP) : 0;
		usleep(g_phi.tt_sleep * 1000);
		(g_phi.dead == false) ? display_act(philo->phi_nb + 1, S_THINK) : 0;
	}
	return (NULL);
}
