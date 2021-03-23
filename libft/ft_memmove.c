/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:23:15 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/20 19:53:01 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_memcpy_rev(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0)
		return (dest);
	while (n--)
		((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
	return (dest);
}

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return (ft_memcpy_rev(dest, src, n));
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	return (0);
}
