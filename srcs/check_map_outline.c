/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_outline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:19 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/23 17:48:57 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_diff(char *current_line, char *past_line, int diff)
{
	char	*line_long;
	char	*line_short;
	int		i;

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
			return (0);
	return (1);
}

//check droite puis dessous puis gauche

int	check_closed(char **map, int i, int j, int last)
{
	int	ret;

	ret = 0;
	if (map[i][j + 1] == '1' || map[i][j + 1] == ' ')
		ret++;
	if (last)
		if (map[i + 1][j] == '1' || map[i + 1][j] == ' ')
			ret++;
	if (map[i][j - 1] == '1' || map[i][j - 1] == ' ')
		ret++;
	if (map[i - 1][j] == '1' || map[i - 1][j] == ' ')
		ret++;
	if (last && ret == 4)
		return (1);
	else if (!last && ret == 3)
		return (1);
	return (0);
}

int	check_space_closed(char **map, int i, int j, int limit)
{
	int	ret;

	ret = 1;
	if (i == limit - 1)
		return (2);
	if (map[i][j + 1] == ' ')
		ret = check_space_closed(map, i, j + 1, limit);
	else if (map[i + 1][j] == ' ')
		ret = check_space_closed(map, i + 1, j, limit);
	else if (map[i + 1][j + 1] == ' ')
		ret = check_space_closed(map, i + 1, j + 1, limit);
	if (!check_closed(map, i, j, 1))
		return (0);
	return (ret);
}

int	check_space(char **map, int i, int j)
{
	while (map[i][++j])
	{
		if (map[i][j] == ' ')
			if (check_space_closed(map, i, j, map_length(map)) == 0)
				return (0);
	}
	return (1);
}

int	check_last_line(char **map, int i)
{
	int	j;

	j = -1;
	while (map[i][++j] == ' ')
		;
	while (map[i][++j])
	{
		if (map[i][j] == ' ')
			if (!check_closed(map, i, j, 0))
				return (0);
	}
	return (1);
}
