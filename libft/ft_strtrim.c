/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:00:11 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/05 20:01:51 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t		len;
	const char	*start;
	const char	*end;
	char		*p;
	size_t		tl;

	len = ft_strlen(s1);
	start = s1;
	end = s1 + len - 1;
	while (*start && ft_strchr(set, *start))
		start++;
	while (end > start && ft_strchr(set, *end))
		end--;
	tl = end - start + 1;
	p = malloc(tl + 1);
	if (!p)
		return (0);
	ft_memcpy(p, start, tl);
	p[tl] = '\0';
	return (p);
}
