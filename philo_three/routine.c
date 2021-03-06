/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/03/06 09:00:27 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_kill_processes(t_proc *philo)
{
	int i;

	i = 0;
	while (i < g_philo.philo_nb)
	{
		if (i != philo->philo_nbr)
			kill(g_philo.pid[i], SIGTERM);
		i++;
	}
}

void	*ft_monitor_routine(void *arg)
{
	t_proc *philo;

	philo = (t_proc *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (g_philo.is_dead == false)
	{
		if ((ft_get_timelaps() - philo->last_time_eat) > g_philo.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			sem_wait(g_philo.display_sem);
			g_philo.is_dead = true;
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_proc *philo)
{
	sem_wait(g_philo.takef_sem);
	sem_wait(g_philo.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	sem_wait(g_philo.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	sem_post(g_philo.takef_sem);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_philo.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_philo.forks_sem);
	sem_post(g_philo.forks_sem);
}

void	*ft_philo_routine(void *arg)
{
	t_proc *philo;

	philo = (t_proc *)arg;
	if (ft_init_monitor(philo))
		return ((void *)PROC_ERROR);
	while (g_philo.is_dead == false)
	{
		ft_eating_routine(philo);
		if (g_philo.is_limited_meal == true && philo->meal_nb == g_philo.meal_limit)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			return (NULL);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_philo.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
	}
	ft_kill_processes(philo);
	return (NULL);
}
