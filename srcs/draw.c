/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 14:46:22 by amdedieu          #+#    #+#             */
/*   Updated: 2021/09/04 17:21:20 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_wall_hit(t_param *param)
{
	if (param->cast.side == 0)
		param->cast.wall_hit = param->cast.posy
			+ param->cast.perpWallDist * param->cast.ray_diry;
	else
		param->cast.wall_hit = (param->cast.perpWallDist * param->cast.ray_dirx)
			+ param->cast.posx;
	param->cast.wall_hit -= floor(param->cast.wall_hit);
}

void	build_t(t_param *param, t_texture *tex, int i)
{
	int				texy;
	int				texx;
	unsigned int	color;

	set_wall_hit(param);
	texx = ((int)(param->cast.wall_hit * (float)tex->w));
	texx = tex->w - texx - 1;
	while (param->cast.draw_start < param->cast.draw_end)
	{
		texy = (param->cast.draw_start * 2 - param->resolution.y
				+ param->cast.line_height) * (tex->h / 2)
			/ param->cast.line_height;
		color = tex->tex_addr[(tex->w * texy) + texx];
		param->mlx.img_addr[param->cast.draw_start
			* param->resolution.x + i] = color;
		param->cast.draw_start++;
	}
}

void	draw_wall(t_param *param, int x)
{
	if (!param->cast.side && param->cast.ray_dirx > 0)
		build_t(param, &param->env.wall_no, x);
	else if (!param->cast.side && param->cast.ray_dirx < 0)
		build_t(param, &param->env.wall_so, x);
	else if (param->cast.side && param->cast.ray_diry > 0)
		build_t(param, &param->env.wall_we, x);
	else if (param->cast.side && param->cast.ray_diry < 0)
		build_t(param, &param->env.wall_ea, x);
}

void	draw_background(t_param *param, int i)
{
	int	j;

	j = 0;
	while (j < param->cast.draw_start)
	{
		param->mlx.img_addr[j * param->resolution.x + i]
			= param->env.color_ceiling;
		j++;
	}
	j = param->cast.draw_end;
	while (j < param->resolution.y)
	{
		param->mlx.img_addr[j * param->resolution.x + i]
			= param->env.color_floor;
		j++;
	}
}
