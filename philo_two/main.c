/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/06/04 15:23:04 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	clear_philo(void)
{
	free(g_phi.philo_threads);
	free(g_phi.to_display);
	sem_close(g_phi.display_sem);
	sem_close(g_phi.finished_meal_sem);
	sem_close(g_phi.forks_sem);
	sem_close(g_phi.takef_sem);
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
	if ((ac != 6 && ac != 5) ||
		!is_arg_digit(av + 1) ||
		(g_phi.philo_nb = ft_atoi(av[1])) < 2 ||
		(g_phi.tt_die = ft_atoi(av[2])) < 0 ||
		(g_phi.tt_eat = ft_atoi(av[3])) < 0 ||
		(g_phi.tt_sleep = ft_atoi(av[4])) < 0 ||
		!(g_phi.to_display = ft_calloc(50)))
	{
		write(1, S_ERR_ARG, ft_strlen(S_ERR_ARG));
		return (ARG_ERROR);
	}
	ft_memcpy(g_phi.to_display, S_STR_TEMPL, ft_strlen(S_STR_TEMPL));
	if ((g_phi.tt_think = (g_phi.tt_die -
			g_phi.tt_eat - g_phi.tt_sleep) / 2) < 0)
		g_phi.tt_think = 1;
	if (av[5])
	{
		if ((g_phi.meal_lim = ft_atoi(av[5])) <= 0)
			return (ARG_ERROR);
		g_phi.is_limited_meal = true;
	}
	else
		g_phi.is_limited_meal = false;
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	int i;

	sem_unlink("finished_meal_sem");
	sem_unlink("display_sem");
	sem_unlink("forks_sem");
	sem_unlink("takef_sem");
	sem_unlink("read_time_sem");
	gettimeofday(&g_startime, NULL);
	if (ft_get_arguments(ac, av) != SUCCESS || ft_set_gphilo() != SUCCESS ||
		ft_init_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (i < g_phi.philo_nb)
	{
		pthread_join(g_phi.philo_threads[i].tid, NULL);
		i++;
	}
	usleep(10000);
	clear_philo();
	return (0);
}
