/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:10:58 by amdedieu          #+#    #+#             */
/*   Updated: 2021/06/28 17:55:11 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <../mlx/mlx.h>
#include "libft.h"
#include <math.h>
# define MOVESPEED 0.2
# define ROTATESPEED 0.1
# define texw 64
# define texh 64
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

typedef struct	s_key
{
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
}				t_key;

typedef struct	s_cast
{
	
	float	posx;
	float	posy;
	float	dirx;
	float	diry;
	float	planx;
	float	plany;
	//float	time;
	//float	old_time;
	float camerax;
	//float cameray 
	float ray_dirx;
	float ray_diry;
    float side_distx;
    float side_disty;
    float delta_distx;
    float delta_disty;
    float perpWallDist;
	int 	**buffer;
	int  screenh;
	int screenw;
	int mapx;
	int mapy;
    int stepX;
    int stepY; 
    int hit;
    int side;
	int line_height;
	int draw_start;
	int draw_end;
	int x_event;
	int x_mask;
	int  color;
}				t_cast;
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
	// position depart
	char posd;
	int posc[2];
}				t_env;

typedef	struct s_mlx
{
	void	*mlx_window;
	void	*mlx_ptr;
	void	*img_ptr;
	char	*img_addr;
	void	*win_ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_mlx;


typedef struct s_param
{
	t_resolution resolution;
	t_env		env;
	t_mlx		mlx;
	t_key		key;
	t_cast		cast;
}				t_param;

//utils.c
char	*trim_spaces(char *buffer);
void	free_tab(char **tab);
int		size_map(char **map);
void		exit_map(char **map);
void 	handle_error(int ret, char **map);

//parsing_map.c
void	parse_map(char **map, t_param  *param);
void	get_pos(char **map, t_param *param);

//parse_utils.c
void	parse_resolution(char *line, int ret, t_param *param);
void	parse_texture(char *line, int ret, t_param *param);
void	parse_color(char *line, int ret, t_param *param);
int		check_if_map(char *line);

//parsing.c
int		ft_parse_file(t_param *param, int fd);

//main.c
void	display_error(char *msg, int code);
//check_map_outline.c
int		check_map_outline(char **map);
