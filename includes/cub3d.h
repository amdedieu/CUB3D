/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:10:58 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/07 12:40:58 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//#include <mlx.h>
#include "libft.h"

// # define CHARSET[1] "./path_to_texture_north"
// # define CHARSET[2] "./path_to_texture_south"
// # define CHARSET[3] "./path_to_texture_west"
// # define CHARSET[4] "./path_to_texture_east"

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
	t_list		**sprites;
	t_texture	sprite_texture;
	//map
	char **map;
}				t_env;

typedef struct s_param
{
	t_resolution resolution;
	t_env		env;
}				t_param;

//utils.c
char	*trim_spaces(char *buffer);

//parsing_map.c
void	parse_map(char **map, t_param  *param);

//parse_utils.c
void	parse_resolution(char *line, int ret, t_param *param);
void	parse_texture(char *line, int ret, t_param *param);
void	parse_color(char *line, int ret, t_param *param);
int		check_if_map(char *line);

//parsing.c
int		ft_parse_file(t_param *param, int fd);

//main.c
void	display_error(char *msg, int code);
