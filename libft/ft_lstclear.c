/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:11:33 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/20 18:50:23 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	int		size;
	t_list	*tmp;

	size = ft_lstsize(*lst);
	tmp = *lst;
	if (lst && *lst && del)
	{
		while (size > 0)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tmp;
			size--;
		}
		*lst = NULL;
	}
}
