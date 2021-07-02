/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/06/30 15:11:23 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	register_sprite(int posx, int posy, t_list **list)
{
	t_sprite *new_sprite;

	new_sprite = malloc(sizeof(t_sprite *));
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
}

void	get_pos(char **map, t_param *param)
{
	int i;
	int j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (param->env.posd == 0)
				{
					param->env.posd = map[i][j];
					param->env.posc[0] = i;
					param->env.posc[1] = j;
				}
				else if (param->env.posd != 0)
				{
					free_tab(map);
					display_error("too many starting positions defined", EXIT_FAILURE);
				}
			}
		}
	}
}

void			parse_map(char **map, t_param *param)
{
	int x;
	int sizex;
	int ret;

	x = 1;
	sizex = size_map(map);
	stock_sprites(map, param);

	if (!check_limit(map[0]) || !check_limit(map[sizex]))
		display_error("Error map", 10);
	get_pos(map, param);
	if (param->env.posd == 0)
		display_error("no starting position defined", EXIT_FAILURE);
	ret = check_map_outline(map); // Recup le code et handle error
	handle_error(ret, map);
}
