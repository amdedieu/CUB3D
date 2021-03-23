/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:10:58 by amdedieu          #+#    #+#             */
/*   Updated: 2021/03/23 22:45:41 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <mlx.h>
#include "libft.h"

typedef struct s_resolution
{
	int x;
	int y;
}				t_resolution;

typedef struct s_texture
{
	char * path;
}				t_texture;

typedef  struct s_sprite
{
	t_texture	texture;
	int		posx;
	int		posy;
}				t_sprite;

typedef struct s_env
{
	//MURS
	t_texture wall_no;
	t_texture wall_so;
	t_texture wall_ea;
	t_texture wall_we;
	//PLAFOND & SOLS
	int color_ceiling;
	int color_floor;
	//SPRITES
	t_sprite  sprites;
}				t_env;

typedef struct s_param
{
	t_resolution resolution;
	t_env		env;
}				t_param;

//utils.c
char	*trim_spaces(char *buffer);
//parse_utils.c
void	parse_resolution(char *line, int ret, t_param *param);
//parsing.c
int		ft_parse_file(t_param *param, int fd);
//main.c
void	display_error(char *msg, int code);
