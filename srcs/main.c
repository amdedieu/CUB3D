/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:35:35 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/07 13:30:35 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		display_error(char *msg, int code)
{
	printf("%s\n", msg);
	exit(code);
}

void		init_param(t_param * param)
{
	param->env.map = NULL;
	param->env.sprites = malloc(sizeof(t_sprite *));
	*param->env.sprites= NULL;
}

int			main(int argc, char **argv)
{
	int		fd;
	t_param	*param;

	if (argc < 2 || argc > 3)
		display_error("wrong parameter number", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		display_error("wrong configuration file", EXIT_FAILURE);
	param = malloc(sizeof(t_param) * 1);
	if (param == NULL)
		return (EXIT_FAILURE);
	init_param(param);
	ft_parse_file(param, fd);
	close(fd);
	return (EXIT_SUCCESS);
}
