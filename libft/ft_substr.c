/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:00:41 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/15 19:57:58 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*tmp;
	char	*tmp2;
	size_t	i;

	i = start;
	if (!(str = malloc(sizeof(char) * len + 1)) || !s)
		return (NULL);
	if (start > ft_strlen((char*)s))
	{
		str[0] = '\0';
		return (str);
	}
	else
	{
		tmp = (char*)s + start;
		tmp2 = str;
		while (*tmp && len-- > 0)
			*tmp2++ = *tmp++;
		*tmp2 = '\0';
	}
	return (str);
}
