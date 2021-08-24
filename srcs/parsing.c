/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:30:34 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/24 14:28:57 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_line(char *line, int ret, t_param *param)
{
	void	(*arr_ptr[7])(char *, int, t_param *);

	arr_ptr[0] = &parse_resolution;
	arr_ptr[1] = &parse_texture;
	arr_ptr[2] = &parse_texture;
	arr_ptr[3] = &parse_texture;
	arr_ptr[4] = &parse_texture;
	arr_ptr[5] = &parse_color;
	arr_ptr[6] = &parse_color;
	arr_ptr[ret](line, ret, param);
}

void	ft_get_map(char *line, int fd, t_param *param)
{
	char	*buffer;

	buffer = NULL;
	while (get_next_line(fd, &buffer))
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
		display_error("No starting position defined", EXIT_FAILURE, param);
}

int	interpret_ret(t_param *param, int ret, char *line, int fd)
{
	if ((check_double_define(param, ret) == 0) || ret == -1)
		display_error("in definition of params", EXIT_FAILURE, param);
	if (ret == 7 && param->env.map == NULL)
	{
		ft_get_map(line, fd, param);
		return (1);
	}
	else if (param->env.map == NULL)
		parse_line(line, ret, param);
	else
		display_error("definition after map", EXIT_FAILURE, param);
	return (0);
}

void	ft_parse_file(t_param *param, int fd)
{
	char	*line;
	char	*origin;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		origin = line;
		if (ft_strlen(line) == 0 || *line == '\n')
		{
			free(origin);
			continue ;
		}
		if (interpret_ret(param, check_line(line), line, fd) == 1)
			break ;
		free(origin);
	}
}
