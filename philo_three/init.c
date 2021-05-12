/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:33:04 by abarot            #+#    #+#             */
/*   Updated: 2021/05/12 17:02:56 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_set_gphilo(void)
{
	if ((!(g_philo.sem.forks =
		sem_open("forks_sem", O_CREAT | O_EXCL, S_IRWXU, g_philo.number)) ||
		!(g_philo.sem.takef =
		sem_open("takef_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.sem.display =
		sem_open("display_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.sem.end_program =
		sem_open("end_program_sem", O_CREAT | O_EXCL, S_IRWXU, 1)) ||
		!(g_philo.sem.finished_meal =
		sem_open("finished_meal_sem", O_CREAT | O_EXCL, S_IRWXU, 1))))
		return (EXIT_FAILURE);
	g_philo.eat_info.meal_nb = 0;
	g_philo.dead = false;
	if (!(g_philo.to_display = ft_calloc(50)) ||
		!(g_philo.pid = malloc(sizeof(pid_t) * g_philo.number)))
		return (EXIT_FAILURE);
	ft_memcpy(g_philo.to_display, S_STR_TEMPL, ft_strlen(S_STR_TEMPL));
	return (EXIT_SUCCESS);
}

int		ft_init_eating_routine(void)
{
	int		err;

	if ((err = pthread_create(&(g_philo.eating_routine), NULL,
				meal_count_routine, &g_philo.number)))
	{
		write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
		return (err);
	}
	pthread_detach(g_philo.eating_routine);
	return (EXIT_SUCCESS);
}

int		ft_init_process(void)
{
	int		i;

	i = 0;
	sem_wait(g_philo.sem.end_program);
	while (i < g_philo.number)
	{
		g_philo.id = i + 1;
		if ((g_philo.pid[i] = fork()) == -1)
			return (EXIT_FAILURE);
		else if (!g_philo.pid[i])
			ft_philo_routine();
		i++;
	}
	if (g_philo.eat_info.is_limited_meal == true)
		ft_init_eating_routine();
	return (EXIT_SUCCESS);
}

int		ft_init_monitor(void)
{
	int err;

	if ((err = pthread_create(&(g_philo.monitor_tid), NULL,
				monitor_routine, NULL)))
	{
		write(1, S_ERR_THREAD, ft_strlen(S_ERR_THREAD));
		return (err);
	}
	pthread_detach(g_philo.monitor_tid);
	return (err);
}
