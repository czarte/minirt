/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:36:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/22 17:17:10 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

bool	handle_identifiers(int camera_count, int light_count, int ambient_count)
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

bool	validate_tokens(char **tokens)
{
	int	count;

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
	{
		printf("Value is: %d\n", bag->i);
		bag->i++;
	}
	if (!strcmp(tokens[0], "L"))
		bag->j++;
	if (!strcmp(tokens[0], "A"))
		bag->k++;
	free_split(tokens);
	return (true);
}
