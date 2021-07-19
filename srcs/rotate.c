/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:45:00 by amdedieu          #+#    #+#             */
/*   Updated: 2021/07/19 14:45:47 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    rotate_right(t_param *param)
{
	float    old_dir;
	float    old_planx;

	old_dir = param->cast.dirx;
	old_planx = param->cast.planx;
	param->cast.dirx = param->cast.dirx * cos(-ROTATESPEED) - param->cast.diry * sin(-ROTATESPEED);
	param->cast.diry = old_dir * sin(-ROTATESPEED) + param->cast.diry * cos(-ROTATESPEED);
	param->cast.planx = param->cast.planx * cos(-ROTATESPEED) - param->cast.plany * sin(-ROTATESPEED);
	param->cast.plany = old_planx * sin(-ROTATESPEED) + param->cast.plany * cos(-ROTATESPEED);
}

void    rotate_left(t_param *param)
{
	float    old_dir;
	float    old_planx;

	old_dir = param->cast.dirx;
	old_planx = param->cast.planx;
	param->cast.dirx = param->cast.dirx * cos(ROTATESPEED) - param->cast.diry * sin(ROTATESPEED);
	param->cast.diry = old_dir * sin(ROTATESPEED) + param->cast.diry * cos(ROTATESPEED);
	param->cast.planx = param->cast.planx * cos(ROTATESPEED) - param->cast.plany * sin(ROTATESPEED);
	param->cast.plany = old_planx * sin(ROTATESPEED) + param->cast.plany * cos(ROTATESPEED);
}

