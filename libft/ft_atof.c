/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:14:09 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/17 14:24:24 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

double	ft_pow(int base, int exp)
{
	double	result;

	result = 1.0;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

int	handle_sign(char *str, int *i, int *sign)
{
	*sign = 1;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
	{
		(*i)++;
	}
	return (1);
}

void	handle_dot(char *str, double *res, int *i)
{
	double	devision;

	devision = 10.0;
	while (ft_isdigit(str[*i]) == 1)
	{
		*res += (str[*i] - '0') / devision;
		devision *= 10.0;
		(*i)++;
	}
}

void	handle_exponenta(char *str, double *res, int *i, int sign)
{
	int		exponenta;

	exponenta = 0;
	while (ft_isdigit(str[*i]))
	{
		exponenta = exponenta * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (sign == -1)
		*res /= ft_pow(10, exponenta);
	else
		*res *= ft_pow(10, exponenta);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	res;
	int		exp_sign;

	i = 0;
	sign = 1;
	res = 0.0;
	exp_sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!handle_sign((char *)str, &i, &sign))
		return (0);
	while (ft_isdigit(str[i]))
		res = res * 10.0 + (str[i++] - '0');
	if (str[i] == '.' && ++i)
		handle_dot((char *)str, &res, &i);
	if (str[i] == 'e' && ++i)
	{
		if (!handle_sign((char *)str, &i, &exp_sign))
			return (0);
		handle_exponenta((char *)str, &res, &i, exp_sign);
	}
	return (res * sign);
}
