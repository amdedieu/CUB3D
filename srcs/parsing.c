/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:30:34 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/06 18:09:39 by amdedieu         ###   ########.fr       */
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

void			ft_get_map(char *line, int fd, t_param *param)
{
	char *buffer;

	(void)param;
	while (get_next_line(fd, &buffer))
	{
		if (ft_strlen(buffer) == 0 || *buffer == '\n')
		{
			free(buffer);
			break ;
		}
		if (check_if_map(buffer) == 1)
		{
			line = ft_strjoin_free1(line, "\n");
			line = ft_strjoin_free(line, buffer);
		}
		else
			display_error("wrong syntaxe for the map", EXIT_FAILURE);
	}
	param->env.map = ft_split(line, '\n');
	printf("fgh\n");
	parse_map(param->env.map);
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

int				ft_parse_file(t_param *param, int fd)
{
	char	*line;
	char	*origin;
	int		ret;

	while (get_next_line(fd, &line))
	{
		origin = line;
		if (ft_strlen(line) == 0 || *line == '\n')
		{
			free(origin);
			continue ;
		}
		ret = check_line(line);
		if (ret == -1)
			display_error("wrong configuration name", EXIT_FAILURE);
		if (ret == 8 && param->env.map == NULL)
			ft_get_map(ft_strdup(line), fd, param);
		else if (param->env.map == NULL)
			parse_line(line, ret, param);
		else
			display_error("definition of parameters after map", EXIT_FAILURE);
		free(origin);
	}
	return (0);
}
