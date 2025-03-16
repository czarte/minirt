/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:32:12 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/04 11:32:16 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		sl;
	int		i;
	char	*res;

	sl = ft_strlen(s);
	i = sl;
	res = NULL;
	if ((char) c == '\0')
		return ((char *)(s + sl));
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			res = ((char *) s + i);
			break ;
		}
		i--;
	}
	return ((char *)res);
}
