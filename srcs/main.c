/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:35:35 by amdedieu          #+#    #+#             */
/*   Updated: 2021/07/19 14:48:37 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		init_param(t_param * param)
{
	param->env.map = NULL;
	param->env.posd = 0;
	param->mlx.mlx_window = 0;
	param->mlx.mlx_ptr = 0;
	param->mlx.img_ptr = 0;
	param->mlx.img_addr = 0;
	param->mlx.win_ptr = 0;
	param->mlx.bpp = 0;
	param->mlx.size_line = 0;
	param->mlx.endian  = 0;
	param->key.a = 0;
	param->key.w = 0;
	param->key.s = 0;
	param->key.d = 0;
}

static void    setup_view(t_param *param)
{
	if ((int)param->env.posd == 'N')
	{
		param->cast.dirx = -1;
		param->cast.plany = 0.66;
	}
	else if ((int)param->env.posd == 'S')
	{
		param->cast.dirx = 1;
		param->cast.plany = -0.66;
	}
	else if ((int)param->env.posd == 'E')
	{
		param->cast.diry = 1;
		param->cast.planx = 0.66;
	}
	else if ((int)param->env.posd == 'W')
	{
		param->cast.diry = -1;
		param->cast.planx = -0.66;
	}
}

void	init_raycast(t_param *param)
{
	//int	buffer[param->cast.screenh][param->cast.screenw];
	param->cast.posx = param->env.posc[0] + 0.5;
	param->cast.posy =  param->env.posc[1] + 0.5;
	param->cast.dirx = 0;
	param->cast.diry = 0;
	param->cast.planx = 0;
	param->cast.plany = 0;
	param->cast.camerax = 0;
	param->cast.ray_dirx = 0;
	param->cast.ray_diry = 0;
	param->cast.side_distx = 0;
	param->cast.side_disty = 0;
	param->cast.mapx = (int)param->env.posc[0];
	param->cast.mapy = (int)param->env.posc[1];
	param->cast.perpWallDist = 0;
	param->cast.stepX = 0;
	param->cast.stepY = 0;
	param->cast.hit = 0;
	param->cast.line_height = 0;
	param->cast.draw_end = 0;
	param->cast.draw_start = 0;
	param->cast.color = 0;
	setup_view(param);
}

void    draw_font(t_mlx *mlx, t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < param->resolution.y)
	{
		j = 0;
		while (j < param->resolution.x)
		{
			*(param->mlx.img_addr + (j * 4 + 0) + (mlx->size_line * i)) =
				(i < param->resolution.y / 2) ? (unsigned)178 : (unsigned)0;
			*(param->mlx.img_addr + (j * 4 + 1) + (mlx->size_line * i)) =
				(i < param->resolution.y / 2) ? (unsigned)34: (unsigned)0;
			*(param->mlx.img_addr + (j * 4 + 2) + (mlx->size_line * i)) =
				(i < param->resolution.y / 2) ? (unsigned)34 : (unsigned)0;
			j++;
		}
		i++;
	}
}

void	draw_tex(t_param *param, int i)
{
	int texy;
	int texx;

	texx = ((int)(param->cast.hit * (float)texw));
	if (param->cast.side == 1 && param->cast.ray_dirx > 0)
		texx = texw - texx - 1;
	if (param->cast.side == 0 && param->cast.ray_diry < 0)
		texx = texw - texx - 1;
	while (param->cast.draw_start < param->cast.draw_end)
	{
		texy = ((((param->cast.draw_start * 256) - (param->resolution.y * 128) +
		(param->cast.line_height * 128)) * texh) / param->cast.line_height) / 256;
		*(param->mlx.img_addr + (i * 4 + 0) + (param->mlx.size_line *
		param->cast.draw_start)) = *(param->mlx.img_addr + (texx * 4 + 0) +
		(param->mlx.size_line * texy));
		*(param->mlx.img_addr + (i * 4 + 1) + (param->mlx.size_line *
		param->cast.draw_start)) = *(param->mlx.img_addr + (texx * 4 + 1) +
		(param->mlx.size_line * texy));
		*(param->mlx.img_addr + (i * 4 + 2) + (param->mlx.size_line *
		param->cast.draw_start)) = *(param->mlx.img_addr + (texx * 4 + 2) +
		(param->mlx.size_line * texy));
		*(param->mlx.img_addr + (i * 4 + 3) + (param->mlx.size_line *
		param->cast.draw_start++)) = *(param->mlx.img_addr + (texx * 4 + 3) +
		(param->mlx.size_line * texy));
	}
}


int		save_bmp(t_param *param)
{
	(void)param;
	return (0);
}
void	__unused	get_event(t_param *param)
{
	(void)param;
		//get_direction()
}

int		 test_func(t_param *param)
{
	int x;

	x = -1;

	ft_move(param);
	draw_font(&(param->mlx), param);

	while(++x < param->resolution.x)
	{
		param->cast.hit = 0;
		param->cast.mapx = (int)param->cast.posx;
		param->cast.mapy = (int)param->cast.posy;
	  	param->cast.camerax = 2 * x / (float)param->resolution.x - 1;
	  	param->cast.ray_dirx = param->cast.dirx + param->cast.planx * param->cast.camerax;
	  	param->cast.ray_diry = param->cast.diry + param->cast.plany * param->cast.camerax;
		param->cast.delta_distx = fabs(1 / param->cast.ray_dirx);
		param->cast.delta_disty = fabs(1 / param->cast.ray_diry);

		if (param->cast.ray_dirx < 0)
	  	{
	  		param->cast.stepX = -1;
	  		param->cast.side_distx = (param->cast.posx - param->cast.mapx) * param->cast.delta_distx;
	 	 }
	 	 else
	  	{
	   		param->cast.stepX = 1;
	   		param->cast.side_distx= (param->cast.mapx + 1.0 - param->cast.posx) * param->cast.delta_distx;
	  	}
	  	if (param->cast.ray_diry < 0)
	  	{
	   		param->cast.stepY = -1;
	   		param->cast.side_disty = (param->cast.posy - param->cast.mapy) * param->cast.delta_disty;
	 	}
	  	else
	  	{
		 param->cast.stepY = 1;
	   	 param->cast.side_disty = (param->cast.mapy + 1 - param->cast.posy) * param->cast.delta_disty;
	  	}
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
		if (param->env.map[param->cast.mapx][param->cast.mapy] == '1' ||
		param->env.map[param->cast.mapx][param->cast.mapy] == '2' ) 
		param->cast.hit = 1;
	  } 
	  if (param->cast.side == 0) 
		param->cast.perpWallDist = (param->cast.mapx - param->cast.posx + (1 - param->cast.stepX) / 2) / param->cast.ray_dirx;
	  else
	  	param->cast.perpWallDist = (param->cast.mapy - param->cast.posy + (1 - param->cast.stepY) / 2) / param->cast.ray_diry;
	   param->cast.line_height = (int)(param->resolution.y / param->cast.perpWallDist);
	   param->cast.draw_start = -(param->cast.line_height) / 2 + param->resolution.y / 2;
	  if (param->cast.draw_start < 0) 
	  	param->cast.draw_start = 0;
	  param->cast.draw_end = param->cast.line_height / 2 + param->resolution.y / 2;
	  if (param->cast.draw_end >= param->resolution.y) 
	  	param->cast.draw_end = param->resolution.y - 1;
  	while(param->cast.draw_start < param->cast.draw_end)
	{
		*(param->mlx.img_addr + (x * 4 + 0) + (param->mlx.size_line * param->cast.draw_start)) = 0;
		*(param->mlx.img_addr + (x * 4 + 1) + (param->mlx.size_line * param->cast.draw_start)) = 0;
		*(param->mlx.img_addr + (x * 4 + 2) + (param->mlx.size_line * param->cast.draw_start)) = 120;
		param->cast.draw_start++;
	}
	}
	mlx_put_image_to_window(param->mlx.mlx_ptr, param->mlx.win_ptr, param->mlx.img_ptr, 0, 0);
	return (0);
}

int		exit_window(t_param  *param)
{
	(void)param;
	exit(0);
}

int		get_number(int key, t_param *param)
{
	(void)param;
	if (key == 13)
		param->key.w = 1;
	if (key == 1)
		param->key.s = 1;	
	if (key == 0)
		param->key.a = 1;
	if (key == 2)
		param->key.d = 1;
	if (key == 123)
		param->key.left = 1;
	if (key == 124)
		param->key.right = 1;
	return (0);
}



void		put_pixel_addr(t_param *param, int x, int y, int color)
{
	char    *dst;

	dst = param->mlx.img_addr + (x * param->mlx.size_line + y * (param->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}

int		push_nbr(int key, t_param *param)
{
	(void)param;
	if (key == 13)
		param->key.w = 0;
	if (key == 1)
		param->key.s = 0;	
	if (key == 0)
		param->key.a = 0;
	if (key == 2)
		param->key.d = 0;
	if (key == 123)
		param->key.left = 0;
	if (key == 124)
		param->key.right= 0;
	
	return (0);
}

void	 cub3d(t_param *param)
{
	init_raycast(param);
	param->mlx.mlx_ptr = mlx_init();
	param->mlx.img_ptr = mlx_new_image(param->mlx.mlx_ptr, param->resolution.x, param->resolution.y);
	param->mlx.img_addr = mlx_get_data_addr(param->mlx.img_ptr, &(param->mlx.bpp), &(param->mlx.size_line), &(param->mlx.endian));
	param->mlx.win_ptr = mlx_new_window(param->mlx.mlx_ptr, param->resolution.x, param->resolution.y, "CUB3D");
	mlx_hook(param->mlx.win_ptr,  17, 0L, exit_window, param);
	mlx_do_key_autorepeatoff(param->mlx.mlx_ptr);
	mlx_hook(param->mlx.win_ptr, 3, 1L<<1, push_nbr, param);
	mlx_hook(param->mlx.win_ptr, 2, 1L<<0, get_number, param);
	mlx_loop_hook(param->mlx.mlx_ptr, test_func, param);
	mlx_loop(param->mlx.mlx_ptr);

}

int			main(int argc, char **argv)
{
	int		fd;
	t_param	*param;

	if (argc < 2 || argc > 4)
		display_error("wrong parameter number", EXIT_FAILURE);
	if (argc == 3 && !(ft_strncmp(argv[2], "--save", 6)))
		display_error("invalid third argument", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error("wrong configuration file", EXIT_FAILURE);
	
	param = malloc(sizeof(t_param) * 1);
	if (param == NULL)
		return (EXIT_FAILURE);
	init_param(param);
	ft_parse_file(param, fd);
	close(fd);
	if (argc == 3)
		save_bmp(param);
	else
		cub3d(param);
	
	return (EXIT_SUCCESS);
}
