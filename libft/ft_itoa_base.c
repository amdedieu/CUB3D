/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 03:17:42 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/30 15:34:46 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned int n, char *base)
{
	char		*str;

	str = (char *)ft_calloc(sizeof(char), 2);
	if (!(str))
		return (NULL);
	if ((int)n < 0)
	{
		str[0] = '-';
		str[1] = '\0';
		str = ft_strjoin_free(str, ft_itoa_base(-n, base));
	}
	else if (n >= (unsigned int)ft_strlen(base))
	{
		free(str);
		str = ft_strjoin_free(ft_itoa_base(n / ft_strlen(base), base),
				ft_itoa_base(n % ft_strlen(base), base));
	}
	else if (n < (unsigned int)ft_strlen(base) && (int)n >= 0)
	{
		str[0] = base[n];
		str[1] = '\0';
	}
	return (str);
}
