/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:30:34 by amdedieu          #+#    #+#             */
/*   Updated: 2021/03/23 22:49:21 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		parse_line(char *line, int ret, t_param *param)
{
	void	(*arr_ptr[1])(char *, int, t_param *);

	arr_ptr[0] = &parse_resolution;

	arr_ptr[ret](line, ret, param);
}

static int	check_line(char *line)
{
	line = trim_spaces(line);
	if (ft_strncmp(line, "R ", 2) == 0)
		return 0;
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return 1;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return 2;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return 3;	
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return 4;
	else if (ft_strncmp(line, "S ", 2) == 0)
		return 5;
	else if (ft_strncmp(line, "F ", 2) == 0)
		return 6;
	else if (ft_strncmp(line, "C ", 2) == 0)
		return 7;
	return -1;
}

int		ft_parse_file(t_param *param, int fd) // declenche le parsing du fichier
{
	char *line;
	char *origin;
	int ret;

	while (get_next_line(fd, &line))
	{
		origin = line;
		if (ft_strlen(line) == 0)
		{
			free(origin);
			continue ; // retourne a l'iteration en ignorantles instructions suivantes
		}
		// check si l'ID est valide et le return 
		ret = check_line(line); 
		if (ret == -1)
			display_error("wrong configuration name", EXIT_FAILURE); // handle error
		// redirige vers la fonction concernée par l'ID
		parse_line(line, ret, param); 
		free(origin);
	}
	return 0;
}
