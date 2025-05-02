/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 19:36:45 by aevstign          #+#    #+#             */
/*   Updated: 2025/05/02 21:51:07 by aevstign         ###   ########.fr       */
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

bool	check_line(char *line, t_obag *bag)
{
	int		i;
	char	**tokens;

	i = 0;
	while (ft_spacious(line[i]))
		i++;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (false);
	if (!is_valid_identifier(tokens[0]))
	{
		printf("Error: Unknown identifier");
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
