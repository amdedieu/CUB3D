/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 00:45:58 by amdedieu          #+#    #+#             */
/*   Updated: 2021/01/19 00:46:02 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdarg.h"

int		ft_exit(int ret, int n, ...)
{
	va_list		argv;
	void		*temp;
	int			i;

	i = 0;
	va_start(argv, n);
	while (i < n)
	{
		temp = va_arg(argv, void *);
		ft_memdel(&temp);
		i++;
	}
	va_end(argv);
	return (ret);
}
