/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:47:16 by abarot            #+#    #+#             */
/*   Updated: 2021/05/04 12:20:21 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		ft_decimal_nbr(int nbr)
{
	int i;

	i = 1;
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

	if (!(str = ft_calloc(9)))
		return (NULL);
	str = memset(str, '0', 8 - ft_decimal_nbr(nbr));
	ft_looptoa(nbr, str, "0123456789");
	return (str);
}

void	ft_display_action(int nb, char *action)
{
	char	*time_str;
	char	*nbr_str;

	time_str = ft_itoa_time(ft_get_timelaps());
	nbr_str = ft_itoa(nb);
	if (g_philo.is_dead == false)
	{
		sem_wait(g_philo.display_sem);
		write(1, time_str, ft_strlen(time_str));
		write(1, " <", 2);
		write(1, nbr_str, ft_strlen(nbr_str));
		write(1, "> ", 2);
		write(1, " ", 1);
		write(1, action, ft_strlen(action));
		sem_post(g_philo.display_sem);
	}
	free(time_str);
	free(nbr_str);
}

int		ft_get_timelaps(void)
{
	int				laps;
	struct timeval	end;

	gettimeofday(&end, NULL);
	laps = ((end.tv_sec * 1000000 + end.tv_usec) -
	(g_startime.tv_sec * 1000000 + g_startime.tv_usec)) / 1000;
	return (laps);
}
