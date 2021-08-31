/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 17:41:30 by amdedieu          #+#    #+#             */
/*   Updated: 2021/08/30 15:34:46 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list		*temp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		new->next = NULL;
		return ;
	}
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
