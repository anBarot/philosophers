/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:57:49 by abarot            #+#    #+#             */
/*   Updated: 2021/02/16 20:54:29 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int main(int ac, char **av)
{
	gettimeofday(&g_startime, NULL);

	if ((ac != 6 && ac != 5) || ft_set_gphilo(av) == EXIT_FAILURE || 
		ft_init_threads() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (g_philo.is_dead == false && g_philo.is_limit_reached == false)
		usleep(1);
	return (0);
}
