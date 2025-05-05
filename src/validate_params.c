/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:53:24 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/05 14:22:33 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	validate_rgb(char *token)
{
	char	**splited_rgb;
	int		i;
	int		value;

	i = 0;
	splited_rgb = ft_split(token, ',');
	if (!splited_rgb)
		return (false);
	while (splited_rgb[i])
	{
		value = ft_atoi(splited_rgb[i]);
		if (value < 0 || value > 255)
		{
			free_split(splited_rgb);
			return (false);
		}
		i++;
	}
	if (i != 3)
	{
		free_split(splited_rgb);
		return (false);
	}
	free_split(splited_rgb);
	return (true);
}

bool	validate_orientation(char *tokens)
{
	char	**splited_ort;
	t_vec	vec;
	double	x;
	double	y;
	double	z;

	splited_ort = ft_split(tokens, ',');
	if (!splited_ort)
		return (false);
	x = ft_atof(splited_ort[0]);
	y = ft_atof(splited_ort[1]);
	z = ft_atof(splited_ort[2]);
	free_split(splited_ort);
	vec = (t_vec){x, y, z};
	return (vec_length(&vec) > 0.999 && vec_length(&vec) < 1.001);
}

bool	validate_ambient(char **tokens, int count)
{
	double	ratio;

	if (count != 3)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	ratio = ft_atof(tokens[1]);
	if (ratio <= 0.0 || ratio >= 1.0)
	{
		printf("Error: wrong ratio for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[2]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}
