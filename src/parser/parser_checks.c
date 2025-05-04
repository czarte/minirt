/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:36:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/04 23:17:50 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

bool	handle_headers(int camera_count, int light_count, int ambient_count)
{
	if (camera_count != 1)
	{
		printf("Error: Scene must contain exactly one camera (C)\n");
		return (false);
	}
	if (light_count != 1)
	{
		printf("Error: Scene must contain exactly one light (L)\n");
		return (false);
	}
	if (ambient_count != 1)
	{
		printf("Error: Scene must contain exactly one ambient (A)\n");
		return (false);
	}
	return (true);
}

bool	is_valid_identifier(const char *id)
{
	return (!strcmp(id, "A") || !strcmp(id, "C") || !strcmp(id, "L")
		|| !strcmp(id, "sp") || !strcmp(id, "pl") || !strcmp(id, "cy"));
}

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

bool	validate_camera(char **tokens, int count)
{
	int	fov;

	fov = ft_atoi(tokens[3]);
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	if (fov < 0 || fov > 180)
	{
		printf("Error: Wrong fov for camera\n");
		return (false);
	}
	return (true);
}

bool	validate_ambient(char **tokens, int count)
{
	double	ratio;

	if (count != 3)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	ratio = ft_atof(tokens[1]);
	if (ratio <= 0.0 || ratio >= 1.0)
	{
		printf("Error: ambient ratio is wrong\n");
		return (false);
	}
	if (!validate_rgb(tokens[2]))
	{
		printf("Error: wrong color intervals for: %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_light(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for: %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_sphere(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_plane(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for: %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_cylindr(char **tokens, int count)
{
	if (count != 4)
	{
		printf("Error: Wrong number of parameters for: %s\n", tokens[0]);
		return (false);
	}
	if (!validate_rgb(tokens[3]))
	{
		printf("Error: wrong color intervals for: %s\n", tokens[0]);
		return (false);
	}
	return (true);
}

bool	validate_tokens(char **tokens)
{
	int	count;
	int	fov;

	count = 0;
	if (!is_valid_identifier(tokens[0]))
	{
		printf("Error: Unknown identifier '%s'\n", tokens[0]);
		return (false);
	}
	while (tokens[count])
		count++;
	if (!strcmp(tokens[0], "C"))
		return (validate_camera(tokens, count));
	if (!strcmp(tokens[0], "A"))
		return (validate_ambient(tokens, count));
	if (!strcmp(tokens[0], "L"))
		return (validate_light(tokens, count));
	if (!strcmp(tokens[0], "sp"))
		return (validate_sphere(tokens, count));
	if (!strcmp(tokens[0], "pl") && count != 4)
		return (validate_plane(tokens, count));
	if (!strcmp(tokens[0], "cy"))
		return (validate_cylindr(tokens, count));
	return (true);
}

bool	check_line(char *line, t_obag *bag)
{
	int		i;
	char	**tokens;

	i = 0;
	while (ft_spacious(line[i]))
		i++;
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (false);
	if (!validate_tokens(tokens))
	{
		free_split(tokens);
		return (false);
	}
	if (!strcmp(tokens[0], "C"))
		bag->i++;
	if (!strcmp(tokens[0], "L"))
		bag->j++;
	if (!strcmp(tokens[0], "A"))
		bag->k++;
	free_split(tokens);
	return (true);
}
