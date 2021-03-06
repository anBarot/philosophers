/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/03/06 10:36:35 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_get_arguments(char **av)
{
	if ((g_philo.philo_nb = ft_atoi(av[1])) < 2 ||
		(g_philo.time_to_die = ft_atoi(av[2])) < 0 ||
		(g_philo.time_to_eat = ft_atoi(av[3])) < 0 ||
		(g_philo.time_to_sleep = ft_atoi(av[4])) < 0)
	{
		write(1, S_ERR_ARG, ft_strlen(S_ERR_ARG));
		return (ARG_ERROR);
	}
	if (av[5])
	{
		if ((g_philo.meal_limit = ft_atoi(av[5])) < 0)
			return (ARG_ERROR);
		g_philo.is_limited_meal = true;
	}
	else
		g_philo.is_limited_meal = false;
	return (SUCCESS);
}

int		main(int ac, char **av)
{
	sem_unlink("finished_meal_sem");
	sem_unlink("display_sem");
	sem_unlink("forks_sem");
	sem_unlink("takef_sem");
	gettimeofday(&g_startime, NULL);
	if ((ac != 6 && ac != 5) || ft_get_arguments(av) != SUCCESS ||
			ft_set_gphilo() != SUCCESS ||
			ft_init_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (g_philo.is_dead == false &&
			g_philo.nb_finished_threads != g_philo.philo_nb)
		usleep(1);
	return (0);
}
