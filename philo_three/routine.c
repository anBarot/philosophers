/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 12:12:13 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*ft_monitor_routine(void *arg)
{
	t_proc *philo;

	philo = (t_proc *)arg;
	philo->last_time_eat = get_timelaps();
	while (philo->dead == false && !(g_phi.is_limited_meal == true &&
	philo->meal_nb == g_phi.meal_lim))
	{
		if ((get_timelaps() - philo->last_time_eat) >= g_phi.tt_die)
		{
			display_act(philo->phi_nb, S_DIE);
			sem_wait(g_phi.display_sem);
			philo->dead = true;
			sem_post(g_phi.end_program_sem);
		}
	}
	return (NULL);
}

void	eating_routine(t_proc *philo)
{
	sem_wait(g_phi.takef_sem);
	sem_wait(g_phi.forks_sem);
	display_act(philo->phi_nb, S_FORK);
	sem_wait(g_phi.forks_sem);
	display_act(philo->phi_nb, S_FORK);
	display_act(philo->phi_nb, S_EAT);
	sem_post(g_phi.takef_sem);
	philo->last_time_eat = get_timelaps();
	usleep(g_phi.tt_eat * 1000);
	philo->meal_nb = philo->meal_nb + 1;
	sem_post(g_phi.forks_sem);
	sem_post(g_phi.forks_sem);
}

void	ft_philo_routine(t_proc *philo)
{
	if (ft_init_monitor(philo))
		exit(PROC_ERROR);
	while (philo->dead == false)
	{
		eating_routine(philo);
		if (g_phi.is_limited_meal == true && philo->meal_nb == g_phi.meal_lim
			&& philo->dead == false)
		{
			display_act(philo->phi_nb, S_REACHED);
			g_phi.tt_die = __INT_MAX__;
			free(g_phi.philo_proc);
			sem_post(g_phi.finished_meal_sem);
			while (1)
				usleep(1);
		}
		display_act(philo->phi_nb, S_SLEEP);
		usleep(g_phi.tt_sleep * 1000);
		display_act(philo->phi_nb, S_THINK);
	}
	while (1)
		usleep(1);
}
