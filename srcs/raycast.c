/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 16:34:44 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/24 14:27:23 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_raycast(t_param *param, int x)
{
	param->cast.hit = 0;
	param->cast.mapx = (int)param->cast.posx;
	param->cast.mapy = (int)param->cast.posy;
	param->cast.camerax = 2 * x / (float)param->resolution.x - 1;
	param->cast.ray_dirx = param->cast.dirx + param->cast.planx
		* param->cast.camerax;
	param->cast.ray_diry = param->cast.diry + param->cast.plany
		* param->cast.camerax;
	param->cast.delta_distx = fabs(1 / param->cast.ray_dirx);
	param->cast.delta_disty = fabs(1 / param->cast.ray_diry);
}

void	build_ray(t_param *param)
{
	if (param->cast.ray_dirx < 0)
	{
		param->cast.stepX = -1;
		param->cast.side_distx = (param->cast.posx - param->cast.mapx)
			* param->cast.delta_distx;
	}
	else
	{
		param->cast.stepX = 1;
		param->cast.side_distx = (param->cast.mapx + 1.0 - param->cast.posx)
			* param->cast.delta_distx;
	}
	if (param->cast.ray_diry < 0)
	{
		param->cast.stepY = -1;
		param->cast.side_disty = (param->cast.posy - param->cast.mapy)
			* param->cast.delta_disty;
	}
	else
	{
		param->cast.stepY = 1;
		param->cast.side_disty = (param->cast.mapy + 1 - param->cast.posy)
			* param->cast.delta_disty;
	}
}

void	build_wall(t_param *param)
{
	if (param->cast.side == 0)
		param->cast.perpWallDist = (param->cast.mapx - param->cast.posx
				+ (1 - param->cast.stepX) / 2) / param->cast.ray_dirx;
	else
		param->cast.perpWallDist = (param->cast.mapy - param->cast.posy
				+ (1 - param->cast.stepY) / 2) / param->cast.ray_diry;
	param->cast.line_height = (int)(param->resolution.y
			/ param->cast.perpWallDist);
	param->cast.draw_start = -(param->cast.line_height)
		/ 2 + param->resolution.y / 2;
	if (param->cast.draw_start < 0)
		param->cast.draw_start = 0;
	param->cast.draw_end = param->cast.line_height
		/ 2 + param->resolution.y / 2;
	if (param->cast.draw_end >= param->resolution.y)
		param->cast.draw_end = param->resolution.y - 1;
}

void	find_wall(t_param	*param)
{
	while (param->cast.hit == 0)
	{
		if (param->cast.side_distx < param->cast.side_disty)
		{
			param->cast.side_distx += param->cast.delta_distx;
			param->cast.mapx += param->cast.stepX;
			param->cast.side = 0;
		}
		else
		{
			param->cast.side_disty += param->cast.delta_disty;
			param->cast.mapy += param->cast.stepY;
			param->cast.side = 1;
		}
		if (param->env.map[param->cast.mapx][param->cast.mapy] == '1')
			param->cast.hit = 1;
	}
}

int	raycasting(t_param *param)
{
	int	x;

	x = -1;
	ft_move(param);
	draw_font(&(param->mlx), param);
	while (++x < param->resolution.x)
	{
		init_raycast(param, x);
		build_ray(param);
		find_wall(param);
		build_wall(param);
		draw_wall(param, x);
	}
	mlx_put_image_to_window(param->mlx.mlx_ptr, param->mlx.win_ptr,
		param->mlx.img_ptr, 0, 0);
	return (0);
}
