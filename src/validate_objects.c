/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:47:21 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/17 14:25:12 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	validate_camera(char **tokens, int count)
{
	int	fov;

	fov = ft_atoi(tokens[3]);
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	if (fov < 0 || fov > 180)
	{
		printf("Error: Wrong fov for camera\n");
		return (false);
	}
	if (!validate_orientation(tokens[2]))
	{
		printf("Error: Wrong orientation for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_light(char **tokens, int count)
{
	double	ratio;

	if (count != 4)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	ratio = ft_atof(tokens[2]);
	if (ratio <= 0.0 || ratio >= 1.0)
	{
		printf("Error: wrong ratio for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_sphere(char **tokens, int count)
{
	double	diameter;

	if (count != 4)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	diameter = ft_atof(tokens[2]);
	if (diameter < 0)
	{
		printf("Error: Diametr should be positive for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_plane(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_orientation(tokens[2]))
	{
		printf("Error: Wrong orientation for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_cylindr(char **tokens, int count)
{
	double	height;

	if (count != 6)
	{
		printf("Error: Wrong number of parameters for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[5]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	if (!validate_orientation(tokens[2]))
	{
		printf("Error: Wrong orientation for %s\n", tokens[0]);
		return (false);
	}
	height = ft_atof(tokens[4]);
	if (height < 0)
	{
		printf("Error: Height should be positive for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}
