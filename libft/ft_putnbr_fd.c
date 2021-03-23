/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:07:14 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/20 18:19:58 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int nb, int fd)
{
	if (fd >= 0)
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			if (nb == -2147483648)
			{
				ft_putchar_fd('2', fd);
				nb = -147483648;
			}
			nb *= -1;
		}
		if (nb > 9)
		{
			ft_putnbr_fd(nb / 10, fd);
			nb %= 10;
		}
		ft_putchar_fd(nb + 48, fd);
	}
}
