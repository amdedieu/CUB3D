/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:44:26 by amdedieu          #+#    #+#             */
/*   Updated: 2021/09/03 15:57:11 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(char *line, int ret, t_param *param)
{
	line = trim_spaces(line);
	line += 2;
	line = trim_spaces(line);
	if (ret == 0)
		param->env.wall_no.path = add_ptr(ft_strdup(line), param->addr);
	else if (ret == 1)
		param->env.wall_so.path = add_ptr(ft_strdup(line), param->addr);
	else if (ret == 2)
		param->env.wall_we.path = add_ptr(ft_strdup(line), param->addr);
	else if (ret == 3)
		param->env.wall_ea.path = add_ptr(ft_strdup(line), param->addr);
	printf("nord %s\n", param->env.wall_no.path);
	printf("sud %s\n", param->env.wall_so.path);
	printf("est %s\n", param->env.wall_ea.path);
	printf("ouest %s\n", param->env.wall_we.path);
}

int	check_line(char *line)
{
	line = trim_spaces(line);	
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (2);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (4);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (5);
	else if (check_if_map(line) == 1)
		return (6);
	return (-1);
}

int	check_double_define(t_param *param, int ret)
{
	if (ret == 0)
		if (param->resolution.x != 0 && param->resolution.y != 0)
			return (2);
	if (ret == 1)
		if (param->env.wall_no.path != NULL)
			return (3);
	if (ret == 2)
		if (param->env.wall_so.path != NULL)
			return (4);
	if (ret == 3)
		if (param->env.wall_we.path != NULL)
			return (5);
	if (ret == 4)
		if (param->env.wall_ea.path != NULL)
			return (6);
	if (ret == 5)
		if (param->env.color_floor != 0)
			return (7);
	if (ret == 6)
		if (param->env.color_ceiling != 0)
			return (8);
	return (1);
}
