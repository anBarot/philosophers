/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/03/06 09:24:26 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*monitor_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_philo.is_dead == false ||
	!(g_philo.is_limited_meal == true && philo->meal_nb == g_philo.meal_limit))
	{
		if ((ft_get_timelaps() - philo->last_time_eat) > g_philo.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			pthread_mutex_lock(&g_philo.display_mutex);
			g_philo.is_dead = true;
		}
	}
	return (NULL);
}

void	ft_eating_routine_even(t_thread *philo)
{
	pthread_mutex_lock(&(g_philo.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_lock(&(g_philo.forks_mutex[(philo->philo_nbr + 1)
						% g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	pthread_mutex_lock(&(philo->monitor_mutex));
	philo->last_time_eat = ft_get_timelaps();
	pthread_mutex_unlock(&(philo->monitor_mutex));
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	pthread_mutex_unlock(&(g_philo.forks_mutex[(philo->philo_nbr + 1)
							% g_philo.philo_nb]));
	pthread_mutex_unlock(&(g_philo.forks_mutex[philo->philo_nbr]));
}

void	ft_eating_routine_odd(t_thread *philo)
{
	pthread_mutex_lock(&(g_philo.forks_mutex[(philo->philo_nbr + 1)
							% g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_lock(&(g_philo.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	pthread_mutex_unlock(&(g_philo.forks_mutex[philo->philo_nbr]));
	pthread_mutex_unlock(&(g_philo.forks_mutex[(philo->philo_nbr + 1)
							% g_philo.philo_nb]));
}

void	*philo_routine(void *arg)
{
	t_thread *philo;

	philo = (t_thread *)arg;
	if (ft_init_monitor(philo))
		return ((void *)THREAD_ERROR);
	while (1)
	{
		if (philo->philo_nbr % 2 == 0)
			ft_eating_routine_even(philo);
		else
			ft_eating_routine_odd(philo);
		if (g_philo.is_limited_meal == true &&
			philo->meal_nb == g_philo.meal_limit)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			pthread_mutex_lock(&g_philo.finished_meal_mutex);
			g_philo.nb_finished_threads = g_philo.nb_finished_threads + 1;
			pthread_mutex_unlock(&g_philo.finished_meal_mutex);
			pthread_exit((void *)MEAL_NB_REACHED);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_philo.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
	}
	return (NULL);
}
