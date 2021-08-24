/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 14:46:22 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/23 15:27:38 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	build_t(t_param *param, t_texture *tex, int texx, int i)
{
	int	texy;

	texy = ((((param->cast.draw_start * 256) - (param->resolution.y * 128)
					+ (param->cast.line_height * 128)) * tex->h)
			/ param->cast.line_height) / 256;
	*(param->mlx.img_addr + (i * 4 + 0) + (param->mlx.size_line
				* param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 0)
			+ (tex->size_line * texy));
	*(param->mlx.img_addr + (i * 4 + 1) + (param->mlx.size_line
				* param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 1)
			+ (tex->size_line * texy));
	*(param->mlx.img_addr + (i * 4 + 2) + (param->mlx.size_line
				* param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 2)
			+ (tex->size_line * texy));
	*(param->mlx.img_addr + (i * 4 + 3) + (param->mlx.size_line
				* param->cast.draw_start++)) = *(tex->tex_addr + (texx * 4 + 3)
			+ (tex->size_line * texy));
}

void	draw_tex(t_param *param, t_texture *tex, int i)
{
	int	texx;

	texx = ((int)(param->cast.wall_hit * (float)tex->w));
	if (param->cast.side == 0 && param->cast.ray_dirx > 0)
		texx = tex->w - texx - 1;
	if (param->cast.side == 1 && param->cast.ray_diry < 0)
		texx = tex->w - texx - 1;
	while (param->cast.draw_start < param->cast.draw_end)
		build_t(param, tex, texx, i);
}

void	draw_wall(t_param *param, int x)
{
	if (param->cast.side == 0)
		param->cast.wall_hit = param->cast.posy
			+ param->cast.perpWallDist * param->cast.ray_diry;
	else
		param->cast.wall_hit = (param->cast.perpWallDist * param->cast.ray_dirx)
			+ param->cast.posx;
	param->cast.wall_hit -= floor(param->cast.wall_hit);
	if (param->cast.side == 0)
	{
		if (param->cast.perpWallDist * param->cast.ray_dirx > 0)
			draw_tex(param, &(param->env.wall_no), x);
		else
			draw_tex(param, &(param->env.wall_so), x);
	}
	else if (param->cast.side == 1)
	{
		if (param->cast.perpWallDist * param->cast.ray_diry > 0)
			draw_tex(param, &(param->env.wall_ea), x);
		else
			draw_tex(param, &(param->env.wall_we), x);
	}
}

unsigned int	calc_font(t_param *param, int i, int code)
{
	if (code == 1 && i < param->resolution.y / 2)
		return (178);
	if (code == 2 && i < param->resolution.y / 2)
		return (34);
	if (code == 3 && i < param->resolution.y / 2)
		return (34);
	return (0);
}

void	draw_font(t_mlx *mlx, t_param *param)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < param->resolution.y)
	{
		j = 0;
		while (j < param->resolution.x)
		{
			*(param->mlx.img_addr + (j * 4 + 0) + (mlx->size_line * i))
				= calc_font(param, i, 1);
			*(param->mlx.img_addr + (j * 4 + 1) + (mlx->size_line * i))
				= calc_font(param, i, 2);
			*(param->mlx.img_addr + (j * 4 + 2) + (mlx->size_line * i))
				= calc_font(param, i, 3);
			j++;
		}
		i++;
	}
}
