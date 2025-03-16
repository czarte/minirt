/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:36:00 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/13 16:37:49 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rcpy(char *dst, const char *src, size_t n);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	else if (dst < src)
		ft_memcpy((char *) dst, (char *) src, len);
	else if (dst > src)
		ft_rcpy((char *) dst, (char *) src, len);
	return (dst);
}

static void	*ft_rcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (n > 0)
	{
		dst[i] = src[i];
		i--;
		n--;
	}
	return (dst);
}
