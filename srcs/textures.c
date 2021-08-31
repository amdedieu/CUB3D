/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:50:58 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/23 16:27:19 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_texture(t_texture *tex, t_param *param)
{
	tex->tex_ptr = mlx_xpm_file_to_image(param->mlx.mlx_ptr,
			tex->path, &tex->w, &tex->h);
	if (!(tex->tex_ptr))
		exit_window(param, "error, texture failed\n");
	tex->tex_addr = mlx_get_data_addr(tex->tex_ptr,
			&(tex->bpp), &(tex->size_line), &(param->mlx.bpp));
}

void	get_all_texture(t_param	*param)
{
	get_texture(&param->env.wall_no, param);
	get_texture(&param->env.wall_so, param);
	get_texture(&param->env.wall_ea, param);
	get_texture(&param->env.wall_we, param);
}
