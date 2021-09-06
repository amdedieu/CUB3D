/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:18:41 by amdedieu          #+#    #+#             */
/*   Updated: 2021/09/04 17:26:38 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_spaces(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] && buffer[i] == ' ')
		i++;
	return (buffer + i);
}

void	exit_map(char **map, t_param *param)
{
	free_tab(map);
	display_error("wrong format for the map", EXIT_FAILURE, param);
}

int	size_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i - 1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	leave_prog(void *param)
{
	exit_window((t_param *)param, "Leaving program");
	return (1);
}
