/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:50:32 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/03 20:51:35 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(size_t c)
{
	if (c <= 'Z' && c >= 'A')
		return (c = c + 32);
	else
		return (c);
}
