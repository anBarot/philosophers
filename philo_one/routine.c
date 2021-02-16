/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/02/16 19:39:16 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*death_monitor_routine(void *arg)
{
	int i;

	death_monitor.last_time_eat = ft_get_timelaps();
	while (g_philo.ending == false)
	{
		i = 0;
		while (i < g_philo.philo_nb)
		{
			if ((ft_get_timelaps() - g_death_monitor.last_time_eat[i]) 
				> g_philo.time_to_die)
			{
				g_philo.ending = true;
				g_death_monitor.who_died = i;
				break;
			}
			i++;
		}
	}
	return (NULL);
}

void	ft_eating_routine_even(t_thread *philo)
{
	pthread_mutex_lock(&(g_philo.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_lock(&(g_philo.forks_mutex[(philo->philo_nbr + 1) % g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	death_monitor.last_time_eat[philo->philo_nbr] = ft_get_timelaps();
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	pthread_mutex_unlock(&(g_philo.forks_mutex[philo->philo_nbr]));
	pthread_mutex_unlock(&(g_philo.forks_mutex[(philo->philo_nbr + 1) % g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_SLEEP);
	usleep(g_philo.time_to_sleep * 1000);
	ft_display_action(philo->philo_nbr, S_THINK);
}

void	ft_eating_routine_odd(t_thread *philo)
{
	pthread_mutex_lock(&(g_philo.forks_mutex[(philo->philo_nbr + 1) % g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_FORK);
	pthread_mutex_lock(&(g_philo.forks_mutex[philo->philo_nbr]));
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	death_monitor.last_time_eat[philo->philo_nbr] = ft_get_timelaps();
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	pthread_mutex_unlock(&(g_philo.forks_mutex[philo->philo_nbr]));
	pthread_mutex_unlock(&(g_philo.forks_mutex[(philo->philo_nbr + 1) % g_philo.philo_nb]));
	ft_display_action(philo->philo_nbr, S_SLEEP);
	usleep(g_philo.time_to_sleep * 1000);
	ft_display_action(philo->philo_nbr, S_THINK);
}

void	*philo_routine(void *arg)
{
	t_thread *philo;
	t_death_monitor death_monitor;
	int err;

	philo = (t_thread *)arg;
	if ((err = pthread_create(&(death_monitor.tid), NULL, death_monitor_routine, philo)))
	{
		write(1, S_ERR_thread, ft_strlen(S_ERR_thread));
		return (EXIT_FAILURE);
	}
	pthread_detach(death_monitor.tid);
	while (g_philo.is_limited_meal == false || (g_philo.is_limited_meal == true && philo->meal_nb != g_philo.meal_limit))
	{
		if (philo->philo_nbr % 2 == 0)
			ft_eating_routine_even(philo);
		else
			ft_eating_routine_odd(philo);
	}
	return (NULL);
}
