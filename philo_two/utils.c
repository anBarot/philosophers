/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:08:27 by abarot            #+#    #+#             */
/*   Updated: 2021/03/06 10:24:28 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_calloc(int size)
{
	char *res;

	if (!size)
		size = 1;
	if (!(res = malloc(size)))
		return (NULL);
	while (size)
	{
		res[size - 1] = '\0';
		size--;
	}
	return ((void *)res);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

int		ft_atoi(char *str)
{
	int				sign;
	unsigned int	nbr;

	sign = 1;
	nbr = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + *str - '0';
		str++;
	}
	return (nbr * sign);
}

void	ft_looptoa(int nbr, char *res, char *base)
{
	if (nbr >= ft_strlen(base))
		ft_looptoa(nbr / ft_strlen(base), res, base);
	res[ft_strlen(res)] = base[nbr % ft_strlen(base)];
}

char	*ft_itoa(int nbr)
{
	char *str;

	if (!(str = ft_calloc(12)))
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		ft_looptoa(nbr, str + 1, "0123456789");
	}
	else
		ft_looptoa(nbr, str, "0123456789");
	return (str);
}
