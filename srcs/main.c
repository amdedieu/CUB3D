#include "../includes/cub3d.h"

void		init_param(t_param * param)
{
	param->addr = malloc(sizeof(t_list *));
	if(!param->addr)
		display_error("malloc failed",EXIT_FAILURE, param);
	*param->addr = NULL;
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
	param->cast.wall_hit = 0;
	param->cast.line_height = 0;
	param->cast.draw_end = 0;
	param->cast.draw_start = 0;
	param->cast.color = 0;
	setup_view(param);
}

static void    draw_tex(t_param *param, t_texture *tex, int i)
{
    int texy;
    int texx;

    texx = ((int)(param->cast.wall_hit * (float)tex->w));
    if (param->cast.side == 0 && param->cast.ray_dirx > 0)
        texx = tex->w - texx - 1;
    if (param->cast.side == 1 && param->cast.ray_diry < 0)
        texx = tex->w - texx - 1;
    while (param->cast.draw_start < param->cast.draw_end)
    {
		 texy = ((((param->cast.draw_start * 256) - (param->resolution.y * 128) + (param->cast.line_height * 128)) * tex->h) / param->cast.line_height) / 256;
        *(param->mlx.img_addr + (i * 4 + 0) + (param->mlx.size_line *
        param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 0) +
        (tex->size_line * texy));
        *(param->mlx.img_addr + (i * 4 + 1) + (param->mlx.size_line *
        param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 1) +
        (tex->size_line * texy));
        *(param->mlx.img_addr + (i * 4 + 2) + (param->mlx.size_line *
        param->cast.draw_start)) = *(tex->tex_addr + (texx * 4 + 2) +
        (tex->size_line * texy));
        *(param->mlx.img_addr + (i * 4 + 3) + (param->mlx.size_line *
        param->cast.draw_start++)) = *(tex->tex_addr + (texx * 4 + 3) +
        (tex->size_line * texy));
	//printf("%Lf, %i, %i\n", param->cast.wall_hit, tex->h, tex->size_line);
    }
}

static void    draw_wall(t_param *param, int x)
{
    if (param->cast.side == 0)
        param->cast.wall_hit = param->cast.posy + param->cast.perpWallDist * param->cast.ray_diry;
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
		draw_wall(param, x);
	}
	mlx_put_image_to_window(param->mlx.mlx_ptr, param->mlx.win_ptr, param->mlx.img_ptr, 0, 0);
	return (0);
}


int		exit_window(t_param  *param)
{
		display_error("program leaved successfully", EXIT_SUCCESS, param);
		return (1);
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
	if(key == 53)
		display_error("program leaved successfully", EXIT_SUCCESS, param);
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

static void		get_texture(t_texture *tex, t_param *param)
{
	tex->tex_ptr = mlx_xpm_file_to_image(param->mlx.mlx_ptr,
		tex->path, &tex->w, &tex->h);
	if (!(tex->tex_ptr))
		display_error("texture failed", 12, param);
	tex->tex_addr = mlx_get_data_addr(tex->tex_ptr,
		&(tex->bpp), &(tex->size_line), &(param->mlx.bpp));
}

static void		get_all_texture(t_param	*param)
{
	get_texture(&param->env.wall_no, param);
	get_texture(&param->env.wall_so, param);
	get_texture(&param->env.wall_ea, param);
	get_texture(&param->env.wall_we, param);
}

void	 cub3d(t_param *param)
{
	init_raycast(param);
	param->mlx.mlx_ptr = mlx_init();
	param->mlx.img_ptr = mlx_new_image(param->mlx.mlx_ptr, param->resolution.x, param->resolution.y);
	param->mlx.img_addr = mlx_get_data_addr(param->mlx.img_ptr, &(param->mlx.bpp), &(param->mlx.size_line), &(param->mlx.endian));
	param->mlx.win_ptr = mlx_new_window(param->mlx.mlx_ptr, param->resolution.x, param->resolution.y, "CUB3D");
	get_all_texture(param);
	mlx_hook(param->mlx.win_ptr,  17, 0L, exit_window, param);
	mlx_do_key_autorepeatoff(param->mlx.mlx_ptr);
	mlx_hook(param->mlx.win_ptr, 3, 1L<<1, push_nbr, param);
	mlx_hook(param->mlx.win_ptr, 2, 1L<<0, get_number, param);
	mlx_loop_hook(param->mlx.mlx_ptr, test_func, param);
	mlx_loop(param->mlx.mlx_ptr);
}

static int	ft_is_valid_file(char *str)
{
	char *ext;

	ext = str;
	while (ft_strchr(ext, '.'))
		ext = ft_strchr(ext, '.') + 1;
	if (ft_strncmp(ext, "cub\0", 4) == 0)
		return (1);
	return  (0);	
}

static int check_param(t_param *param)
{
	if (param->resolution.x == 0 || param->resolution.y == 0)
		display_error("missing parameters for resolution", EXIT_FAILURE, param);
	if (!param->env.wall_no.path || !param->env.wall_ea.path ||
		!param->env.wall_so.path || !param->env.wall_ea.path)
		display_error("missing textures for a wall", EXIT_FAILURE, param);
	if (!param->env.color_floor|| !param->env.color_ceiling)
		display_error("missing color for ceiling or floor", EXIT_FAILURE, param);
	if (!param->env.map)
		display_error("missing map", EXIT_FAILURE, param);
	return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_param	*param;

	param = malloc(sizeof(t_param) * 1);
	if (param == NULL)
		return (EXIT_FAILURE);
	init_param(param);
	if (argc < 2 || argc > 4)
		display_error("wrong parameter number", EXIT_FAILURE, param);
	if (argc == 3 && !(ft_strncmp(argv[2], "--save", 6)))
		display_error("invalid third argument", EXIT_FAILURE, param);
	 if (ft_is_valid_file(argv[1]) == 0)
		display_error("wrong extension name", EXIT_FAILURE, param);	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error("wrong configuration file", EXIT_FAILURE, param);
	
	ft_parse_file(param, fd);
	close(fd);
	check_param(param);
	display_error("c un test en sah", EXIT_FAILURE, param);
	cub3d(param);
	
	return (EXIT_SUCCESS);
}
