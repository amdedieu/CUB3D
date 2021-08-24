#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define MOVESPEED 0.09
# define ROTATESPEED 0.05

typedef struct s_resolution
{
	int	x;
	int	y;
}				t_resolution;

typedef struct s_texture
{
	char		*path;
	int			h;
	int			w;
	char		*tex_addr;
	void		*tex_ptr;
	int			size_line;
	int			bpp;
	int			endian;
}				t_texture;

typedef struct s_sprite
{
	int		posx;
	int		posy;
}				t_sprite;

typedef struct s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}				t_key;

typedef struct s_cast
{
	float		posx;
	float		posy;
	float		dirx;
	float		diry;
	float		planx;
	float		plany;
	float		camerax;
	float		ray_dirx;
	float		ray_diry;
	long double	wall_hit;
	float		side_distx;
	float		side_disty;
	float		delta_distx;
	float		delta_disty;
	float		perpWallDist;
	int			**buffer;
	int			screenh;
	int			screenw;
	int			mapx;
	int			mapy;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x_event;
	int			x_mask;
	int			color;
}	t_cast;

typedef struct s_env
{
	t_texture	wall_no;
	t_texture	wall_so;
	t_texture	wall_ea;
	t_texture	wall_we;
	int			color_ceiling;
	int			color_floor;
	t_texture	sprite_texture;
	char		**map;
	char		posd;
	int			posc[2];
}	t_env;

typedef struct s_mlx
{
	void	*mlx_window;
	void	*mlx_ptr;
	void	*img_ptr;
	char	*img_addr;
	void	*win_ptr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_param
{
	t_resolution	resolution;
	t_env			env;
	t_list			**addr;
	t_mlx			mlx;
	t_key			key;
	t_cast			cast;
}	t_param;

// error.c
void	handle_error(int ret, t_param *param);
void	display_error(char *msg, int code, t_param *param);
int		exit_window(t_param *param, char *msg);

// utils.c
char	*trim_spaces(char *buffer);
void	free_tab(char **tab);
int		size_map(char **map);
void	exit_map(char **map, t_param *param);

// parsing_map.c
void	parse_map(char **map, t_param *param);
void	get_pos(char **map, t_param *param);
int		check_map_outline(char **map);
int		map_length(char **map);
int		check_param(t_param *param);

// parse_utils.c
void	parse_resolution(char *line, int ret, t_param *param);
void	parse_texture(char *line, int ret, t_param *param);
void	parse_color(char *line, int ret, t_param *param);
int		check_line(char *line);
int		check_double_define(t_param *param, int ret);

// movement.c
void	move_right(float dirx, float diry, t_param *param);
void	move_left(float dirx, float diry, t_param *param);
void	move_front(float dirx, float diry, t_param *param);
void	move_back(float dirx, float diry, t_param *param);
void	ft_move(t_param *param);

// addr_collector.c
void	*add_ptr(void *content, t_list **list);

// draw.c
void	draw_tex(t_param *param, t_texture *tex, int i);
void	draw_wall(t_param *param, int x);
void	draw_font(t_mlx *mlx, t_param *param);

// key.c
int		get_number(int key, t_param *param);
int		push_nbr(int key, t_param *param);

// textures.c
void	get_all_texture(t_param	*param);
void	get_texture(t_texture *tex, t_param *param);

// rotate.c
void	rotate_right(t_param *param);
void	rotate_left(t_param *param);

// raycast.c
int		raycasting(t_param *param);
void	init_struct(t_param *param);

// parsing.c
void	ft_parse_file(t_param *param, int fd);
int		check_length(char *buffer);

// check.c
void	init_struct(t_param *param);
int		check_param(t_param *param);
int		check_length(char *buffer);
int		check_if_map(char *line);

// main.c
void	setup_view(t_param *param);
void	init_param(t_param *param);
void	put_pixel_addr(t_param *param, int x, int y, int color);

// check_map_outline.c
int		check_last_line(char **map, int i);
int		check_space(char **map, int i, int j);
int		check_space_closed(char **map, int i, int j, int limit);
int		check_closed(char **map, int i, int j, int last);
int		check_diff(char *current_line, char *past_line, int diff);
#endif
