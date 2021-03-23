/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:33:06 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/15 16:31:59 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (s2[i] == '\0')
		return ((char*)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		i -= j;
		while (s1[i] == s2[j] && s2[j] && i < len)
		{
			j++;
			if (s2[j] == '\0')
				return ((char*)s1 + i - (j - 1));
			i++;
		}
		i++;
	}
	return (NULL);
}
