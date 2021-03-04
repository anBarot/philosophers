/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:47:16 by abarot            #+#    #+#             */
/*   Updated: 2021/03/03 17:32:02 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int ft_decimal_nbr(int nbr)
{
	int i = 1;

	while (nbr >= 10)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_time(int nbr)
{
	char *str;

	if (!(str = ft_calloc(8)))
		return (NULL);
	str = memset(str, '0', 8 - ft_decimal_nbr(nbr));
	if (nbr < 0)
	{
		str[0] = '-';
		ft_looptoa(nbr, str + 1, "0123456789");
	}
	else
		ft_looptoa(nbr, str, "0123456789");
	return (str);
}

void ft_display_action(int nb, char *action)
{
	if (g_philo.is_dead == false)
	{
		sem_wait(g_philo.display_sem);
		write(1, ft_itoa_time(ft_get_timelaps()), 12);
		write(1, " <", 2);
		write(1, ft_itoa(nb), ft_strlen(ft_itoa(nb)));
		write(1, "> ", 2);
		write(1, " ", 1);
		write(1, action, ft_strlen(action));
		sem_post(g_philo.display_sem);
	}
}

int ft_get_timelaps()
{
	int	laps;
	t_timeval end;

	gettimeofday(&end, NULL);
	laps = ((end.tv_sec * 1000000 + end.tv_usec) -
    (g_startime.tv_sec * 1000000 + g_startime.tv_usec)) / 1000;
	return (laps);
}