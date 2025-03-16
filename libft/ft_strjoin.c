/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:35 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/05 19:31:11 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	ml;
	size_t	s1len;

	s1len = ft_strlen(s1);
	if (!s1 || !s2)
		return (NULL);
	ml = s1len + ft_strlen(s2);
	p = malloc((ml + 1) * sizeof (char));
	if (!p)
		return (NULL);
	ft_memcpy(p, (const void *) s1, s1len);
	ft_memcpy(p + s1len, (const void *) s2, ml - s1len);
	p[ml] = '\0';
	return (p);
}
