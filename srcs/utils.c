/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 21:18:41 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/14 19:23:16 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_spaces(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] && buffer[i] == ' ')
		i++;
	return (buffer + i);
}

void		exit_map(char **map)
{
	free_tab(map);
	display_error("wrong format for the map", EXIT_FAILURE);
}

int		size_map(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i - 1);
}

void handle_error(int ret, char **map)
{
	
	if(ret == 10)
	{
		free_tab(map);
		display_error("missing 1 on top of a line", EXIT_FAILURE);
	}
	else if(ret == 11)
	{
		free_tab(map);
		display_error("map is not surrounded by 1", EXIT_FAILURE);
	}
	else if(ret == 12)
	{
		free_tab(map);
		display_error("space is not surrounded by 1", EXIT_FAILURE);
	}
	else if(ret == 13)
	{
		free_tab(map);
		display_error("missing 1 at the end of a line", EXIT_FAILURE);
	}
}

void		free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
}
