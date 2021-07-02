/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_outline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:19 by amdedieu          #+#    #+#             */
/*   Updated: 2021/04/14 12:52:44 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int __unused map_length(char ** map)
{
	int i = 0;
	while (map[i++])
		;
	return i - 1;
}

static void __unused display(char **map)
{
	for (int i = 0; map[i]; ++i)
		printf("line[%3d] %s\n", i, map[i]);
}

static int check_diff(char * current_line, char * past_line, int diff)
{
	char * line_long;
	char * line_short;
	int i;

	if (diff > 0)
	{
		line_long = current_line;
		line_short = past_line;
	}
	else
	{
		line_long = past_line;
		line_short = current_line;
	}
	i = ft_strlen(line_short) - 1;
	while (line_long[++i])
		if (line_long[i] != '1')
			return 0;
	return 1;
}

// Supprimer 'X'
static int check_closed(char ** map, int i, int j, int last)
{
	int ret = 0;

	if (map[i][j + 1] == '1' || map[i][j + 1] == 'X' || map[i][j + 1] == ' ') // a droite
		ret++;
	if (last)
		if (map[i + 1][j] == '1' || map[i + 1][j] == 'X' || map[i + 1][j] == ' ') // en dessous
			ret++;
	if (map[i][j - 1] == '1' || map[i][j - 1] == 'X' || map[i][j - 1] == ' ')  // a gauche
		ret++;
	if (map[i - 1][j] == '1' || map[i - 1][j] == 'X' || map[i - 1][j] == ' ') // au dessus
		ret++;

	if (last && ret == 4)
		return 1;
	else if (!last && ret == 3)
		return 1;
	return 0;
}

static int check_space_closed(char **map, int i, int j, int limit)
{
	int ret = 1;

	if (i == limit - 1)
		return 2;

	if (map[i][j + 1] == ' ')
	 ret = check_space_closed(map, i, j + 1, limit);
	else if (map[i + 1][j] == ' ')
	 ret = check_space_closed(map, i + 1, j, limit);
	else if (map[i + 1][j + 1] == ' ')
	 ret = check_space_closed(map, i + 1, j + 1, limit);

	if (!check_closed(map, i, j, 1))
		return 0;

	// if (ret == 1)
	// {
	// 	map[i][j] = 'X';
	// 	printf("marking : %d %d\n", i, j);
	// 	display(map);
	// 	sleep(1);
	// 	system("clear");
	// }
	// if (ret == 2)
	// 	map[i][j] = 'X';

	// if (ret == 0)
	// 	map[i][j] = 'X';

	return ret;
}

static int check_space(char **map, int i, int j)
{
	while (map[i][++j])
	{
		if (map[i][j] == ' ')
			if (check_space_closed(map, i, j, map_length(map)) == 0)
				return 0;
	}
	return 1;
}

static int check_last_line(char ** map, int i)
{
	int j = -1;
	while (map[i][++j] == ' ')
		;
	while (map[i][++j])
	{
		if (map[i][j] == ' ')
			if (!check_closed(map, i, j, 0))
				return 0;
	}
	return 1;
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
			return 12; // espace dans la map non fermer
	}
	if (!check_last_line(map, --i))
		return 13; // fin de ligne pas fermé
	display(map);
	return 1; // tout ok
}

