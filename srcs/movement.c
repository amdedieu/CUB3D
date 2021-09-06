/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/09/06 13:56:33 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_right(float dirx, float diry, t_param *param)
{
	float	tempx;
	float	tempy;

	tempy = param->cast.posy - (MOVESPEED * dirx);
	tempx = param->cast.posx + (MOVESPEED * diry);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(param->env.map[param->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(param->env.map))
		exit_window(param, "You left the map");
	param->cast.posy = tempy;
	param->cast.posx = tempx;
}

void	move_left(float dirx, float diry, t_param *param)
{
	float	tempx;
	float	tempy;

	tempy = param->cast.posy + (MOVESPEED * dirx);
	tempx = param->cast.posx - (MOVESPEED * diry);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(param->env.map[param->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(param->env.map))
		exit_window(param, "You left the map");
	param->cast.posy = tempy;
	param->cast.posx = tempx;
}

void	move_front(float dirx, float diry, t_param *param)
{
	float	tempx;
	float	tempy;

	tempy = param->cast.posy + (MOVESPEED * diry);
	tempx = param->cast.posx + (MOVESPEED * dirx);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(param->env.map[param->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(param->env.map))
		exit_window(param, "You left the map");
	param->cast.posy = tempy;
	param->cast.posx = tempx;
}

void	move_back(float dirx, float diry, t_param *param)
{
	float	tempx;
	float	tempy;

	tempy = param->cast.posy - (MOVESPEED * diry);
	tempx = param->cast.posx - (MOVESPEED * dirx);
	if ((int)tempy <= 0 || (int)tempy + 1
		>= (int)ft_strlen(param->env.map[param->cast.mapx]) || (int)tempx <= 0
		|| (int)tempx >= size_map(param->env.map))
		exit_window(param, "You left the map");
	param->cast.posy = tempy;
	param->cast.posx = tempx;
}

void	ft_move(t_param *param)
{
	if (param->key.d == 1)
		move_right(param->cast.dirx, param->cast.diry, param);
	if (param->key.w == 1)
		move_front(param->cast.dirx, param->cast.diry, param);
	if (param->key.a == 1)
		move_left(param->cast.dirx, param->cast.diry, param);
	if (param->key.s == 1)
		move_back(param->cast.dirx, param->cast.diry, param);
	if (param->key.left == 1)
		rotate_left(param);
	if (param->key.right == 1)
		rotate_right(param);
}