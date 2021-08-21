/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 12:48:40 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/20 19:11:21 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	display_error(char *msg, int code, t_param *param)
{
	int i;

	i = 0;
	if (param->env.map != NULL)
	{
		while (param->env.map[i])
			free(param->env.map[i++]);
		free(param->env.map);
	}
	ft_lstclear(param->addr, free);
	free(param->addr);
	// free(param);
	// param = NULL;
	if (code != 0)
		printf("Error, ");
	printf("%s\n", msg);	
	system("leaks Cub3D");
	exit(code);
}

void handle_error(int ret, t_param *param)
{
	
	if(ret == 10)
		display_error("missing 1 on top of a line", EXIT_FAILURE, param);
	else if(ret == 11)
		display_error("map is not surrounded by 1", EXIT_FAILURE, param);
	else if(ret == 12)
		display_error("space is not surrounded by 1", EXIT_FAILURE, param);
	else if(ret == 13)
		display_error("missing 1 at the end of a line", EXIT_FAILURE, param);
}
