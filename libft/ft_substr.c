/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:49:40 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/05 15:50:12 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	sl;

	sl = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (sl <= start)
		return (ft_strdup(""));
	if ((sl - start) < len)
		len = (sl - start);
	p = ft_calloc(len + 1, sizeof (char));
	if (!p)
		return (NULL);
	ft_memcpy(p, s + start, len);
	p[len] = '\0';
	return (p);
}
