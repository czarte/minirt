/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:00:42 by voparkan          #+#    #+#             */
/*   Updated: 2023/11/25 15:51:42 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbrtstr(char *ptr_tab, long i, int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	char	*str[11];
	long	num;

	if (n == 0)
		write(fd, &"0", 1);
	else
	{
		if (n < 0)
		{
			write(fd, &"-", 1);
			num = (long) n * -1;
		}
		else
			num = (long) n;
		ft_bzero(str, 10);
		ft_nbrtstr((char *)str, num, 0, fd);
	}
}

static void	ft_nbrtstr(char *ptr_tab, long i, int n, int fd)
{
	char	ch;

	if (i > 0)
	{
		ch = (char)(i % 10 + '0');
		ptr_tab[n] = ch;
		i = i / 10;
		n++;
		ft_nbrtstr(ptr_tab, i, n, fd);
	}
	else
	{
		if (n > 0)
		{
			n--;
			write(fd, &ptr_tab[n], 1);
			ft_nbrtstr(ptr_tab, i, n, fd);
		}
	}
}
