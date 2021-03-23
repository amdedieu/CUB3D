/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:20:11 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/20 20:15:23 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*res;

	if (lst)
	{
		if (!(res = ft_lstnew(f(lst->content))))
		{
			ft_lstdelone(res, del);
			return (NULL);
		}
		res->next = ft_lstmap(lst->next, f, del);
		return (res);
	}
	return (NULL);
}
