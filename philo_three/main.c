/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/03/03 17:32:04 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int main(int ac, char **av)
{
	sem_unlink("finished_meal_sem");
	sem_unlink("display_sem");
	sem_unlink("forks_sem");
	sem_unlink("takef_sem");
	gettimeofday(&g_startime, NULL);
	if ((ac != 6 && ac != 5) || ft_set_gphilo(av) == EXIT_FAILURE || 
		ft_init_threads() == EXIT_FAILURE)
	{
		write(1, S_INIT_FAIL, ft_strlen(S_INIT_FAIL));
		return (EXIT_FAILURE);
	}
	while (g_philo.is_dead == false && g_philo.nb_finished_threads != g_philo.philo_nb)
		usleep(1);
	return (0);
}
