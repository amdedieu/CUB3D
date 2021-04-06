/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/06 18:12:54 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		size_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i - 1);
}

static	int		check_limit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

static void		free_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
}

void			parse_map(char **map)
{
	int x;
	int y;
	int sizex;
	int sizey;

	x = 1;
	sizex = size_map(map);
	if (check_limit(map[0]) && check_limit(map[sizex]))
	{
		while (map[x] != 0)
		{
			y = 0;
			sizey = (int)ft_strlen(map[x]) - 1;
			while (map[x][y] == ' ')
				y++;
			if (map[x][y] == '1' && map[x][sizey] == '1')
				x++;
			else
			{
				free_map(map);
				display_error("missing wall", EXIT_FAILURE);
			}
		}
	}
}
