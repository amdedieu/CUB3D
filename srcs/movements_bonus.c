/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:42:07 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/23 15:56:03 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_right(float dirx, float diry, t_param *param)
{
	if (param->env.map[(int) param->cast.posx]
		[(int)(param->cast.posy - (MOVESPEED) * dirx)] != '1')
		param->cast.posy -= (MOVESPEED * dirx);
	if (param->env.map[(int)(param->cast.posx + (MOVESPEED * diry))]
		[(int)param->cast.posy] != '1')
		param->cast.posx += (MOVESPEED * diry);
}

void	move_left(float dirx, float diry, t_param *param)
{
	if (param->env.map[(int)(param->cast.posx)]
		[(int)(param->cast.posy +(MOVESPEED * param->cast.dirx))] != '1')
		param->cast.posy += (MOVESPEED * dirx);
	if (param->env.map[(int)(param->cast.posx - MOVESPEED * param->cast.diry)]
		[(int)param->cast.posy] != '1')
		param->cast.posx -= (MOVESPEED * diry);
}

void	move_front(float dirx, float diry, t_param *param)
{
	if (param->env.map[(int)(param->cast.posx)]
		[(int)(param->cast.posy + MOVESPEED * param->cast.diry)] != '1')
		param->cast.posy += (MOVESPEED * diry);
	if (param->env.map[(int)(param->cast.posx + (MOVESPEED * param->cast.dirx))]
		[(int)param->cast.posy] != '1')
		param->cast.posx += (MOVESPEED * dirx);
}

void	move_back(float dirx, float diry, t_param *param)
{
	if (param->env.map[(int)(param->cast.posx)]
		[(int)(param->cast.posy - MOVESPEED * param->cast.diry)] != '1')
		param->cast.posy -= (MOVESPEED * diry);
	if (param->env.map[(int)(param->cast.posx - (MOVESPEED * param->cast.dirx))]
		[(int)param->cast.posy] != '1')
		param->cast.posx -= (MOVESPEED * dirx);
}

void	ft_move(t_param *param)
{
	if (param->key.d == 1)
		move_right(param->cast.dirx, param->cast.diry, param);
	if (param->key.w == 1)
		move_front(param->cast.dirx, param->cast.diry, param);
	if (param->key.a == 1)
		move_left(param->cast.dirx, param->cast.diry, param);
	if (param->key.s == 1)
		move_back(param->cast.dirx, param->cast.diry, param);
	if (param->key.left == 1)
		rotate_left(param);
	if (param->key.right == 1)
		rotate_right(param);
}
