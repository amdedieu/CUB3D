/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:48:40 by amdedieu          #+#    #+#             */
/*   Updated: 2021/07/19 12:50:57 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		display_error(char *msg, int code)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(code);
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
