/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:30:34 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/20 17:15:37 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		parse_line(char *line, int ret, t_param *param)
{
	void	(*arr_ptr[8])(char *, int, t_param *);

	arr_ptr[0] = &parse_resolution;
	arr_ptr[1] = &parse_texture;
	arr_ptr[2] = &parse_texture;
	arr_ptr[3] = &parse_texture;
	arr_ptr[4] = &parse_texture;
	arr_ptr[5] = &parse_texture;
	arr_ptr[6] = &parse_color;
	arr_ptr[7] = &parse_color;
	arr_ptr[ret](line, ret, param);
}

int				check_length(char *buffer)
{
	if (!ft_strlen(buffer) || *buffer == '\n')
	{
		free(buffer);
		return (1);
	}
	return (0);
}

void			ft_get_map(char *line, int fd, t_param *param)
{
	char *buffer;
	int ret =  0;

	buffer = NULL;
	while ((ret = get_next_line(fd, &buffer)))
	{
		if (check_length(buffer))
			continue ;
		if (check_if_map(buffer) == 1)
		{
			line = ft_strjoin_free1(line, "\n");
			line = ft_strjoin_free(line, buffer);
 		}
		else
		{
			free(buffer);
			display_error("wrong syntaxe for the map", EXIT_FAILURE, param);
		}
	}
	param->env.map = ft_split(line, '\n');
	free(line);
	free(buffer);
	parse_map(param->env.map, param);
	if (param->env.posd == 0)
		display_error("No starting position  defined", EXIT_FAILURE, param);
}

static int		check_line(char *line)
{
	line = trim_spaces(line);
	if (ft_strncmp(line, "R ", 2) == 0)
		return (0);
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (2);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (4);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (5);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (6);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (7);
	else if (check_if_map(line) == 1)
		return (8);
	return (-1);
}
static int check_double_define(t_param *param, int ret)
{
	if (ret == 0)
		if(param->resolution.x != 0 && param->resolution.y != 0)
			return (0);
	if (ret == 1)
		if(param->env.wall_no.path != NULL)
			return (0);
	if (ret == 2)
		if(param->env.wall_so.path != NULL)
			return (0);
	if (ret == 3)
		if(param->env.wall_we.path != NULL)
			return (0);
	if (ret == 4)
		if(param->env.wall_ea.path != NULL)
			return (0);
	if (ret == 6)
		if(param->env.color_floor != 0)
			return (0);
	if (ret == 7)
		if(param->env.color_ceiling != 0)
			return (0);
	return  (1);
}
int				ft_parse_file(t_param *param, int fd)
{
	char	*line;
	char	*origin;
	int		ret;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		origin = line;
		if (ft_strlen(line) == 0 || *line == '\n')
		{
			free(origin);
			continue ;
		}
		ret = check_line(line);
		if (check_double_define(param, ret) == 0) // origin pas free si call display error
			display_error("mutiple definition of parameters", EXIT_FAILURE, param);
		if (ret == -1)
			display_error("wrong or double configuration name", EXIT_FAILURE, param);
		if (ret == 8 && param->env.map == NULL)
		{
			ft_get_map(line, fd, param);
			return (0);
		}
		else if (param->env.map == NULL)
			parse_line(line, ret, param);
		else
			display_error("definition of parameters after map", EXIT_FAILURE, param);
		free(origin);
	}
	return (0);
}
