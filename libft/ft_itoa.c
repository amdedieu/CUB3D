/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:04:00 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/15 20:07:35 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	nb;

	nb = n;
	i = len(nb);
	if (i == 0)
		i++;
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i--] = '\0';
	nb == 0 ? res[0] = 48 : 0;
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		res[i--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (res);
}
