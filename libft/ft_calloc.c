/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 09:46:52 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/22 14:39:28 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;

	if (!(size) || !(nmemb))
		return (NULL);
	if (!(str = malloc((size * nmemb))))
		return (NULL);
	ft_bzero(str, (nmemb * size));
	return (str);
}
