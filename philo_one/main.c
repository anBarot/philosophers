/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/05/06 18:22:39 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

void	clear_philo(void)
{
	free(g_phi.forks_mutex);
	free(g_phi.philo_threads);
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
	if ((g_phi.time_to_think = (g_phi.time_to_die -
			g_phi.time_to_eat - g_phi.time_to_sleep) / 2) < 0)
		g_phi.time_to_think = 1;
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

	if (ft_get_arguments(ac, av) || ft_set_gphilo() != SUCCESS ||
		ft_init_threads() != SUCCESS)
		return (EXIT_FAILURE);
	i = 0;
	while (i < g_phi.philo_nb)
	{
		pthread_join(g_phi.philo_threads[i].tid, NULL);
		i++;
	}
	while (g_phi.is_dead == false &&
			g_phi.nb_finished_threads != g_phi.philo_nb)
		usleep(1);
	clear_philo();
	return (0);
}
