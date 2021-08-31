/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 17:00:24 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/23 15:38:12 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_number(int key, t_param *param)
{
	(void)param;
	if (key == 13)
		param->key.w = 1;
	if (key == 1)
		param->key.s = 1;
	if (key == 0)
		param->key.a = 1;
	if (key == 2)
		param->key.d = 1;
	if (key == 123)
		param->key.left = 1;
	if (key == 124)
		param->key.right = 1;
	if (key == 53)
		exit_window(param, "program leave successfully");
	return (0);
}

int	push_nbr(int key, t_param *param)
{
	(void)param;
	if (key == 13)
		param->key.w = 0;
	if (key == 1)
		param->key.s = 0;
	if (key == 0)
		param->key.a = 0;
	if (key == 2)
		param->key.d = 0;
	if (key == 123)
		param->key.left = 0;
	if (key == 124)
		param->key.right = 0;
	return (0);
}
