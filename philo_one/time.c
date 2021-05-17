/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:47:16 by abarot            #+#    #+#             */
/*   Updated: 2021/05/17 16:37:20 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		get_timelaps(void)
{
	int				laps;
	struct timeval	end;

	gettimeofday(&end, NULL);
	laps = ((end.tv_sec * 1000000 + end.tv_usec) -
	(g_startime.tv_sec * 1000000 + g_startime.tv_usec)) / 1000;
	return (laps);
}

void	itoa_philo(int nb, int i)
{
	char	*base;

	base = "0123456789";
	while (nb >= 10)
	{
		g_phi.to_display[i] = nb % 10 + '0';
		i--;
		nb = nb / 10;
	}
	g_phi.to_display[i] = nb + '0';
}

void	display_act(int nb, char *action, t_thread *philo)
{
	int start;
	int lost_time;

	start = get_timelaps();
	pthread_mutex_lock(&(g_phi.display_mutex));
	lost_time = get_timelaps() - start;
	philo->last_time_eat = philo->last_time_eat + lost_time;
	itoa_philo(start, 7);
	itoa_philo(nb, 13);
	ft_memcpy(&(g_phi.to_display[ft_strlen(S_STR_TEMPL)]), action,
				ft_strlen(action));
	write(STDOUT_FILENO, g_phi.to_display, ft_strlen(S_STR_TEMPL) +
											ft_strlen(action));
	pthread_mutex_unlock(&(g_phi.display_mutex));
}
