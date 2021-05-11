/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/05/11 19:03:23 by abarot           ###   ########.fr       */
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
	int	i;

	pthread_mutex_destroy(&g_phi.finished_meal_mutex);
	pthread_mutex_unlock(&g_phi.display_mutex);
	pthread_mutex_destroy(&g_phi.display_mutex);
	pthread_mutex_destroy(&g_phi.taking_fork_mutex);
	i = 0;
	while (i < g_phi.philo_nb)
	{
		pthread_mutex_destroy(&g_phi.forks_mutex[i]);
		i++;
	}
	free(g_phi.forks_mutex);
	free(g_phi.read_time_mutex);
	free(g_phi.philo_threads);
	free(g_phi.to_display);
}

int		ft_get_arguments(int ac, char **av)
{
	if ((ac != 6 && ac != 5) ||
		!is_arg_digit(av + 1) ||
		(g_phi.philo_nb = ft_atoi(av[1])) < 2 || g_phi.philo_nb > 9999 ||
		(g_phi.tt_die = ft_atoi(av[2])) < 0 ||
		(g_phi.tt_eat = ft_atoi(av[3])) < 0 ||
		(g_phi.tt_sleep = ft_atoi(av[4])) < 0)
	{
		write(1, S_ERR_ARG, ft_strlen(S_ERR_ARG));
		return (ARG_ERROR);
	}
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
	if (!(g_phi.to_display = ft_calloc(50)))
		return (EXIT_FAILURE);
	ft_memcpy(g_phi.to_display, S_STR_TEMPL, ft_strlen(S_STR_TEMPL));
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
	clear_philo();
	return (0);
}
