/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 13:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/07/19 13:10:44 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int  map_length(char ** map)
{
	int i = 0;
	while (map[i++])
		;
	return i - 1;
}

static	int		check_limit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == ' ')
			i++;
		else
			return (0);
	}
	return (1);
}

void	get_pos(char **map, t_param *param)
{
	int i;
	int j;

	i = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (param->env.posd == 0)
				{
					param->env.posd = map[i][j];
					param->env.posc[0] = i;
					param->env.posc[1] = j;
				}
				else if (param->env.posd != 0)
				{
					free_tab(map);
					display_error("too many starting positions defined", EXIT_FAILURE);
				}
			}
		}
	}
}

int check_map_outline(char **map)
{
	int i = 0;
	int j;
	int diff;

	while (map[++i])
	{
		j = -1;
		while (map[i][++j] == ' ')
			;
		if (map[i][j] != '1')
			return 10; // pas de 1 au debut de la ligne
		diff = ft_strlen(map[i]) - ft_strlen(map[i - 1]);
		if (!check_diff(map[i], map[i - 1], diff))
			return 11; // fin de ligne pas fermer avec diff
		if (!check_space(map, i, j))
			return 12; // espace dans la map non fermé
	}
	if (!check_last_line(map, --i))
		return 13; // fin de ligne pas fermé
	//display(map);
	return 1; // tout ok
}

void			parse_map(char **map, t_param *param)
{
	int x;
	int sizex;
	int ret;

	x = 1;
	sizex = size_map(map);

	if (!check_limit(map[0]) || !check_limit(map[sizex]))
		display_error("Error map", 10);
	get_pos(map, param);
	if (param->env.posd == 0)
		display_error("no starting position defined", EXIT_FAILURE);
	ret = check_map_outline(map); // Recup le code et handle error
	handle_error(ret, map);
}
