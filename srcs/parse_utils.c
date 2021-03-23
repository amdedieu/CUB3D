/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:44:26 by amdedieu          #+#    #+#             */
/*   Updated: 2021/03/23 22:53:46 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_resolution(char *line, int ret, t_param *param)
{
	(void)ret;
	int i;

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

