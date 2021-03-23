/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdedieu <amdedieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:28:14 by amdedieu          #+#    #+#             */
/*   Updated: 2019/10/22 14:24:35 by amdedieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_word(char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			word++;
		while (str[i] == c && str[i + 1] == c)
			i++;
		i++;
	}
	return (word + 1);
}

static char		*ft_worddup(char *s, int n)
{
	char	*res;
	int		i;

	i = 0;
	if (!(res = malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int		ft_find_next_sep(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char			**ft_split(const char *str, char c)
{
	size_t		x;
	int			y;
	char		*s;
	char		**res;

	x = 0;
	s = (char*)str;
	y = ft_count_word(s, c);
	if (!(res = malloc(sizeof(char *) * y + 1)))
		return (NULL);
	y = 0;
	while (x < ft_strlen(s))
	{
		if (ft_find_next_sep(&s[x], c) > 0)
			res[y++] = ft_worddup(&s[x], ft_find_next_sep(&s[x], c));
		else if (ft_find_next_sep(&s[x], c) == -1)
		{
			res[y++] = ft_worddup(&s[x], ft_strlen(&s[x]));
			break ;
		}
		x += ft_find_next_sep(&s[x], c) + 1;
	}
	res[y] = NULL;
	return (res);
}
