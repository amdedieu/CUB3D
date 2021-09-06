/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:01:25 by amdedieu          #+#    #+#             */
/*   Updated: 2021/09/06 12:53:36 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_colour(int r, int g, int b, t_param *param)
{
	int	color;

	color = 65536 * r + 256 * g + b;
	if (r < 0 || r > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE, param);
	if (g < 0 || g > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE, param);
	if (b < 0 || b > 255)
		display_error("wrong number for rgb color", EXIT_FAILURE, param);
	return (color);
}

void	parse_color(char *line, int ret, t_param *param)
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
	if (ret == 4)
		param->env.color_floor = get_colour(r, g, b, param);
	else
		param->env.color_ceiling = get_colour(r, g, b, param);
}
