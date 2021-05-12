/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 11:09:17 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 17:01:42 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*meal_count_routine(int *count)
{
	int	counter;

	counter = *(count) + 1;
	while (counter)
	{
		sem_wait(g_philo.sem.finished_meal);
		counter--;
	}
	sem_post(g_philo.sem.end_program);
	return (NULL);
}

void	*monitor_routine(void)
{
	int	time;

	while (g_philo.dead == false)
	{
		if (g_philo.eat_info.is_limited_meal == true &&
				g_philo.eat_info.meal_nb == g_philo.eat_info.meal_lim)
			break ;
		time = get_timelaps();
		if ((time - g_philo.last_time_eat) >= g_philo.time_to.die)
		{
			display_act(g_philo.id, S_DIE);
			sem_wait(g_philo.sem.display);
			g_philo.dead = true;
			sem_post(g_philo.sem.end_program);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

void	taking_forks(void)
{
	sem_wait(g_philo.sem.takef);
	sem_wait(g_philo.sem.forks);
	display_act(g_philo.id, S_FORK);
	sem_wait(g_philo.sem.forks);
	display_act(g_philo.id, S_FORK);
	sem_post(g_philo.sem.takef);
}

void	eating_routine(void)
{
	taking_forks();
	display_act(g_philo.id, S_EAT);
	g_philo.last_time_eat = get_timelaps();
	usleep(g_philo.time_to.eat * 1000);
	g_philo.eat_info.meal_nb = g_philo.eat_info.meal_nb + 1;
	sem_post(g_philo.sem.forks);
	sem_post(g_philo.sem.forks);
}

void	ft_philo_routine(void)
{
	g_philo.last_time_eat = get_timelaps();
	if (ft_init_monitor(g_philo.monitor_tid))
		exit(PROC_ERROR);
	while (g_philo.dead == false)
	{
		eating_routine();
		if (g_philo.eat_info.is_limited_meal == true &&
				g_philo.eat_info.meal_nb == g_philo.eat_info.meal_lim
				&& g_philo.dead == false)
		{
			display_act(g_philo.id, S_REACHED);
			g_philo.time_to.die = __INT_MAX__;
			free(g_philo.to_display);
			free(g_philo.pid);
			sem_post(g_philo.sem.finished_meal);
			while (1)
				usleep(1);
		}
		display_act(g_philo.id, S_SLEEP);
		usleep(g_philo.time_to.sleep * 1000);
		display_act(g_philo.id, S_THINK);
	}
	while (1)
		usleep(1);
}
