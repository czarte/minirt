/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:08:14 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/15 17:08:57 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*res;	

	i = 0;
	len = ft_strlen(s);
	res = malloc(sizeof (char) * (len + 1));
	if (!s || !f || !res)
		return (0);
	while (i < len)
	{
		res[i] = (*f)(i, (char)s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
