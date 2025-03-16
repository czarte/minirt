/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 16:43:08 by voparkan          #+#    #+#             */
/*   Updated: 2023/04/14 16:43:20 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_makeres(int len, long num, char *res);
static int		countlen(long i);

char	*ft_itoa(int n)
{
	long	num;
	int		neg;
	int		len;
	char	*res;

	num = (long) n;
	neg = 0;
	len = 0;
	if (num < 0)
	{
		neg = 1;
		num = num * -1;
		len++;
	}
	len += countlen(num);
	res = malloc((len + 1) * sizeof (*res));
	if (!res)
		return (0);
	res[len] = '\0';
	ft_makeres(len, num, res);
	if (neg)
		res[0] = '-';
	return (res);
}

static void	ft_makeres(int len, long num, char *res)
{
	while (len-- > 0)
	{
		res[len] = (num % 10) + '0';
		num = num / 10;
	}
}

static int	countlen(long i)
{
	int	len;

	len = 0;
	while (i / 10 > 0)
	{
		i = i / 10;
		len++;
	}
	len++;
	return (len);
}
