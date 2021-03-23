/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 11:04:17 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/15 17:02:24 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	str = (char*)s;
	while (str[size])
		size++;
	while (i < size + 1)
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (0);
}
