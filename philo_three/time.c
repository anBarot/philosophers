/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:47:16 by abarot            #+#    #+#             */
/*   Updated: 2021/06/10 10:55:45 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		get_timelaps(void)
{
	int				laps;
	struct timeval	end;

	gettimeofday(&end, NULL);
	laps = ((end.tv_sec * 1000000 + end.tv_usec) -
	(g_startime.tv_sec * 1000000 + g_startime.tv_usec)) / 1000;
	return (laps);
}

void	itoa_philo(int nb, int i, char *str)
{
	char	*base;

	base = "0123456789";
	while (nb >= 10)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb = nb / 10;
	}
	str[i] = nb + '0';
}

void	display_act(int nb, char *action)
{
	int	write_len;

	write_len = ft_strlen(S_STR_TEMPL) + ft_strlen(action);
	sem_wait(g_philo.sem.display);
	itoa_philo(get_timelaps(), 7, g_philo.to_display);
	itoa_philo(nb, 13, g_philo.to_display);
	ft_memcpy(&(g_philo.to_display[ft_strlen(S_STR_TEMPL)]), action,
				ft_strlen(action));
	write(STDOUT_FILENO, g_philo.to_display, write_len);
	if (g_philo.dead == false)
		sem_post(g_philo.sem.display);
}
