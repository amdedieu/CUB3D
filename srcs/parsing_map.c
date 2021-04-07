/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/07 13:31:23 by amdedieu         ###   ########.fr       */
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

static void		free_tab(char **map) // mettre dans .h et dans utils
{
	int i;

	i = 0;
	while (map[i] != 0)
	{
		free(map[i]);
		i++;
	}
}

static void		exit_map(char **map)
{
	free_tab(map);
	display_error("wrong format for map", EXIT_FAILURE);
}

static void	register_sprite(int posx, int posy, t_list **list)
{
	t_sprite *new_sprite;

	new_sprite = malloc(sizeof(t_sprite));
	if (!new_sprite)
		display_error("register_sprite() : malloc failed", EXIT_FAILURE);
	new_sprite->posx = posx;
	new_sprite->posy = posy;
	ft_lstadd_back(list, ft_lstnew((void *)new_sprite));
}

void	stock_sprites(char **map, t_param *param)
{
	int x;
	int y;

	x = -1;
	y = 0;
	if (!param->env.sprites)
		exit_map(map);
	while (map[++x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '2')
				register_sprite(x, y, param->env.sprites);
			y++;
		}
	}
	print_sprite(param->env.sprites);
}

void			parse_map(char **map, t_param *param)
{
	int x;
	int y;
	int sizex;
	int sizey;

	x = 1;
	sizex = size_map(map);
	stock_sprites(map, param);
	exit(0);
	if (check_limit(map[0]) && check_limit(map[sizex]))
	{
		while (map[x] != 0)
		{
			y = 0;
			sizey = (int)ft_strlen(map[x]) - 1;
			while (map[x][y] == ' ')
				y++;
			if (map[x][y] == '1' && map[x][sizey] == '1')
			{
				x++;
			}
			else
				exit_map(map);
		}
	}
	else
		exit_map(map);
}
