/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 04:08:00 by amdedieu          #+#    #+#             */
/*   Updated: 2021/01/19 04:08:23 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa_unsigned(unsigned int n)
{
	char *str;

	if (!(str = (char *)malloc(sizeof(char) * 2)))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		str = ft_strjoin_free(str, ft_itoa_unsigned(-n));
	}
	else if (n >= 10)
	{
		free(str);
		str = ft_strjoin_free(ft_itoa_unsigned(n / 10),
			ft_itoa_unsigned(n % 10));
	}
	else if (n < 10 && n >= 0)
	{
		str[0] = n + 48;
		str[1] = '\0';
	}
	return (str);
}
