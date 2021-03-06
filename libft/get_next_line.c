/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:47:17 by ameliadedie       #+#    #+#             */
/*   Updated: 2021/08/30 15:34:46 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_refresh_stock(char *stock, int i)
{
	char			*temp;

	if (stock[i])
	{
		temp = ft_strdup(stock + i + 1);
		free(stock);
		stock = temp;
	}
	else
	{
		free(stock);
		stock = NULL;
	}
	return (stock);
}

int	ft_return(int ret, char **buffer, char **stock)
{
	if (ret >= 0 && (*buffer || *stock))
	{
		if (*buffer)
			free(*buffer);
		if (ret == 0 && *stock)
			free(*stock);
	}
	if (ret == -1)
	{
		if (!*buffer)
			free(*buffer);
		if (*stock)
			free(*stock);
	}
	return (ret);
}

int	read_line(int fd, char *buffer, int *ret)
{
	*ret = read(fd, buffer, B_S);
	return (*ret);
}

int	get_next_line(int fd, char **line)
{
	static char		*stock;
	char			*buffer;
	int				ret;
	int				i;

	buffer = (char *)ft_calloc(sizeof(char), (B_S + 1));
	if (B_S <= 0 || !line || fd < 0 || fd > 1024 || !buffer)
		return (ft_return(-1, &buffer, &stock));
	if (!stock)
		stock = (char *)ft_calloc(sizeof(char), 1);
	while (!ft_strchr(buffer, '\n') && read_line(fd, buffer, &ret))
	{
		if (ret == -1)
			return (ft_return(-1, &buffer, &stock));
		buffer[ret] = '\0';
		stock = ft_strjoin_free1(stock, buffer);
	}
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	*line = ft_substr(stock, 0, i);
	stock = ft_refresh_stock(stock, i);
	if (ret || stock)
		return (ft_return(1, &buffer, &stock));
	return (ft_return(0, &buffer, &stock));
}
