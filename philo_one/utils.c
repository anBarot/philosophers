/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarot <abarot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:08:27 by abarot            #+#    #+#             */
/*   Updated: 2021/05/18 11:30:02 by abarot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return (0);
	while (n)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
		n--;
	}
	return (dest);
}

void	*ft_calloc(int size)
{
	char *res;

	if (!size)
		size = 1;
	if (!(res = malloc(size)))
		return (NULL);
	res = memset(res, '\0', size);
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
