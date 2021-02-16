/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/02/16 16:07:20 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int ac, char **av)
{
	gettimeofday(&g_startime, NULL);

	if ((ac != 6 && ac != 5) || ft_set_gphilo(av) == EXIT_FAILURE || 
		ft_init_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (g_philo.ending == false)
		sleep(1);
	if (g_philo.ending == true)
		ft_display_action(g_death_monitor.who_died, S_DIE);
	return (0);
}
