/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/06/04 15:23:45 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_kill_processes(void)
{
	int i;

	i = 0;
	while (i < g_philo.number)
	{
		kill(g_philo.pid[i], SIGTERM);
		i++;
	}
}

void	clear_philo(void)
{
	sem_close(g_philo.sem.display);
	sem_close(g_philo.sem.finished_meal);
	sem_close(g_philo.sem.forks);
	sem_close(g_philo.sem.takef);
	sem_close(g_philo.sem.end_program);
	free(g_philo.pid);
	free(g_philo.to_display);
}

int		is_arg_digit(char **av)
{
	int i;
	int j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_get_arguments(int ac, char **av)
{
	if ((ac != 6 && ac != 5) || !is_arg_digit(av + 1) ||
		(g_philo.number = ft_atoi(av[1])) < 2 ||
		(g_philo.time_to.die = ft_atoi(av[2])) < 0 ||
		(g_philo.time_to.eat = ft_atoi(av[3])) < 0 ||
		(g_philo.time_to.sleep = ft_atoi(av[4])) < 0)
	{
		write(1, S_ERR_ARG, ft_strlen(S_ERR_ARG));
		return (ARG_ERROR);
	}
	if ((g_philo.time_to.think = (g_philo.time_to.die -
			g_philo.time_to.eat - g_philo.time_to.sleep) / 2) < 0)
		g_philo.time_to.think = 1;
	if (av[5])
	{
		if ((g_philo.eat_info.meal_lim = ft_atoi(av[5])) <= 0)
			return (ARG_ERROR);
		g_philo.eat_info.is_limited_meal = true;
	}
	else
		g_philo.eat_info.is_limited_meal = false;
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	sem_unlink("finished_meal_sem");
	sem_unlink("display_sem");
	sem_unlink("forks_sem");
	sem_unlink("takef_sem");
	sem_unlink("end_program_sem");
	gettimeofday(&g_startime, NULL);
	if (ft_get_arguments(ac, av) != SUCCESS ||
		ft_set_gphilo() != SUCCESS || ft_init_process() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sem_wait(g_philo.sem.end_program);
	usleep(1000);
	ft_kill_processes();
	clear_philo();
	return (EXIT_SUCCESS);
}
