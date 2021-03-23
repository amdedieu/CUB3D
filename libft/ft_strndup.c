/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:15:34 by amdedieu          #+#    #+#             */
/*   Updated: 2021/03/23 15:15:48 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strndup(char **s1, int size, int i)
{
	char	*ret;
	int		j;

	j = 0;
	if (size <= i)
	{
		free(*s1);
		*s1 = NULL;
		return (0);
	}
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size && *(*s1 + i))
	{
		ret[j] = *(*s1 + i);
		i++;
		j++;
	}
	ret[j] = '\0';
	free(*s1);
	*s1 = NULL;
	return (ret);
}
