/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:28:31 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/17 17:33:53 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_rev(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0)
		return (dest);
	while (n--)
		((unsigned char*)dest)[n] = ((unsigned char*)src)[n];
	return (dest);
}
