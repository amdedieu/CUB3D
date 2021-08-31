/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:38:39 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/30 15:34:46 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	setup_view(t_param *param)
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

void	init_param(t_param *param)
{
	param->addr = malloc(sizeof(t_list *));
	if (!param->addr)
		display_error("malloc failed", EXIT_FAILURE, param);
	*param->addr = NULL;
	param->env.map = NULL;
	param->env.posd = 0;
	ft_bzero(&param->mlx, sizeof(param->mlx));
	ft_bzero(&param->key, sizeof(param->key));
	ft_bzero(&param->env, sizeof(param->env));
}

void	cub3d(t_param *param)
{
	init_struct(param);
	param->mlx.mlx_ptr = mlx_init();
	get_all_texture(param);
	param->mlx.img_ptr = mlx_new_image(param->mlx.mlx_ptr, param->resolution.x,
			param->resolution.y);
	param->mlx.img_addr = mlx_get_data_addr(param->mlx.img_ptr,
			&(param->mlx.bpp), &(param->mlx.size_line), &(param->mlx.endian));
	param->mlx.win_ptr = mlx_new_window(param->mlx.mlx_ptr, param->resolution.x,
			param->resolution.y, "CUB3D");
	mlx_hook(param->mlx.win_ptr, 17, 0L, exit_window, param);
	mlx_do_key_autorepeatoff(param->mlx.mlx_ptr);
	mlx_hook(param->mlx.win_ptr, 3, 1L << 1, push_nbr, param);
	mlx_hook(param->mlx.win_ptr, 2, 1L << 0, get_number, param);
	mlx_loop_hook(param->mlx.mlx_ptr, raycasting, param);
	mlx_loop(param->mlx.mlx_ptr);
}

static int	ft_is_valid_file(char *str)
{
	char	*ext;

	ext = str;
	while (ft_strchr(ext, '.'))
		ext = ft_strchr(ext, '.') + 1;
	if (ft_strncmp(ext, "cub\0", 4) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_param	*param;

	param = malloc(sizeof(t_param) * 1);
	if (param == NULL)
		return (EXIT_FAILURE);
	init_param(param);
	if (argc > 2)
		display_error("wrong parameter number", EXIT_FAILURE, param);
	 if (ft_is_valid_file(argv[1]) == 0)
		display_error("wrong extension name", EXIT_FAILURE, param);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error("wrong configuration file", EXIT_FAILURE, param);
	ft_parse_file(param, fd);
	close(fd);
	check_param(param);
	cub3d(param);
	return (EXIT_SUCCESS);
}
