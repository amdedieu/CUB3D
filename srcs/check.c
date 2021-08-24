/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 14:27:39 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/24 14:28:31 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_struct(t_param *param)
{
	ft_bzero(&param->cast, sizeof(param->cast));
	param->cast.posx = param->env.posc[0] + 0.5;
	param->cast.posy = param->env.posc[1] + 0.5;
	param->cast.mapx = (int)param->env.posc[0];
	param->cast.mapy = (int)param->env.posc[1];
	setup_view(param);
}

int	check_param(t_param *param)
{
	if (param->resolution.x == 0 || param->resolution.y == 0)
		display_error("missing parameters for resolution", EXIT_FAILURE, param);
	if (!param->env.wall_no.path || !param->env.wall_ea.path
		|| !param->env.wall_so.path || !param->env.wall_ea.path)
		display_error("missing textures for a wall", EXIT_FAILURE, param);
	if (!param->env.color_floor || !param->env.color_ceiling)
		display_error("missing floor or ceiling color", EXIT_FAILURE, param);
	if (!param->env.map)
		display_error("missing map", EXIT_FAILURE, param);
	return (1);
}

int	check_length(char *buffer)
{
	if (!ft_strlen(buffer) || *buffer == '\n')
	{
		free(buffer);
		return (1);
	}
	return (0);
}

int	check_if_map(char *line)
{
	int	i;

	i = 0;
	line = trim_spaces(line);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E'
			|| line[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}
