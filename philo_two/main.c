/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/05/07 14:02:19 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	clear_philo(void)
{
	free(g_phi.philo_threads);
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
		(g_phi.time_to_die = ft_atoi(av[2])) < 0 ||
		(g_phi.time_to_eat = ft_atoi(av[3])) < 0 ||
		(g_phi.time_to_sleep = ft_atoi(av[4])) < 0)
	{
		write(1, S_ERR_ARG, ft_strlen(S_ERR_ARG));
		return (ARG_ERROR);
	}
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
	clear_philo();
	return (0);
}
