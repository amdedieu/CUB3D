/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:44:26 by amdedieu          #+#    #+#             */
/*   Updated: 2021/07/14 18:50:43 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			parse_resolution(char *line, int ret, t_param *param)
{
	int		i;

	(void)ret;
	i = 0;
	line = trim_spaces(line);
	line++;
	line = trim_spaces(line);
	param->resolution.x = ft_atoi(line);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] != ' ')
		display_error("wrong format for resolution", EXIT_FAILURE);
	param->resolution.y = ft_atoi(line + i);
}

void			parse_texture(char *line, int ret, t_param *param)
{
	line = trim_spaces(line);
	if (ret > 0 && ret < 5)
		line += 2;
	else
		line += 1;
	line = trim_spaces(line);
	if (ret == 1)
		param->env.wall_no.path = ft_strdup(line);
	else if (ret == 2)
		param->env.wall_so.path = ft_strdup(line);
	else if (ret == 3)
		param->env.wall_we.path = ft_strdup(line);
	else if (ret == 4)
		param->env.wall_ea.path = ft_strdup(line);
	else if (ret == 5)
		param->env.sprite_texture.path = ft_strdup(line);
}

static	int		get_colour(int r, int g, int b)
{
	int		color;

	color = 65536 * r + 256 * g + b;
	if (r < 0 || r > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE);
	if (g < 0 || g > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE);
	if (b < 0 || b > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE);
	return (color);
}

void			parse_color(char *line, int ret, t_param *param)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	line = trim_spaces(line);
	line += 1;
	line = trim_spaces(line);
	r = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line += i + 1;
	g = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line += i + 1;
	b = ft_atoi(line);
	if (ret == 6)
		param->env.color_floor = get_colour(r, g, b);
	else
		param->env.color_ceiling = get_colour(r, g, b);
}

int				check_if_map(char *line)
{
	int i;

	i = 0;
	line = trim_spaces(line);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0'|| line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E'
			|| line[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
