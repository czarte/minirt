/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vojtechparkan <vojtechparkan@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:54:05 by voparkan          #+#    #+#             */
/*   Updated: 2023/05/28 13:42:00 by vojtechpark      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*p;
	size_t		sz;

	sz = ft_strlen(s1);
	p = malloc(sz + 1);
	if (!p)
		return (0);
	ft_memcpy(p, s1, sz + 1);
	return (p);
}
