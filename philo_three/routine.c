/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/07 15:42:55 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ft_monitor_routine(void *arg)
{
	t_proc *philo;

	philo = (t_proc *)arg;
	philo->last_time_eat = ft_get_timelaps();
	while (philo->is_dead == false && !(g_phi.is_limited_meal == true &&
	philo->meal_nb == g_phi.meal_lim))
	{
		if ((ft_get_timelaps() - philo->last_time_eat) >= g_phi.time_to_die)
		{
			ft_display_action(philo->philo_nbr, S_DIE);
			sem_wait(g_phi.display_sem);
			philo->is_dead = true;
			sem_post(g_phi.end_program_sem);
		}
	}
	return (NULL);
}

void	ft_eating_routine(t_proc *philo)
{
	sem_wait(g_phi.takef_sem);
	sem_wait(g_phi.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	sem_wait(g_phi.forks_sem);
	ft_display_action(philo->philo_nbr, S_FORK);
	ft_display_action(philo->philo_nbr, S_EAT);
	sem_post(g_phi.takef_sem);
	philo->last_time_eat = ft_get_timelaps();
	usleep(g_phi.time_to_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_phi.forks_sem);
	sem_post(g_phi.forks_sem);
}

void	ft_philo_routine(t_proc *philo)
{
	if (ft_init_monitor(philo))
		exit(PROC_ERROR);
	while (philo->is_dead == false)
	{
		ft_eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim
			&& philo->is_dead == false)
		{
			ft_display_action(philo->philo_nbr, S_REACHED);
			g_phi.time_to_die = __INT_MAX__;
			free(g_phi.philo_proc);
			sem_post(g_phi.finished_meal_sem);
			while (1)
				usleep(1);
		}
		ft_display_action(philo->philo_nbr, S_SLEEP);
		usleep(g_phi.time_to_sleep * 1000);
		ft_display_action(philo->philo_nbr, S_THINK);
	}
	while (1)
		usleep(1);
}
