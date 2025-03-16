/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:41 by voparkan          #+#    #+#             */
/*   Updated: 2025/03/16 16:14:41 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_data(s_data *data)
{
	char	*tmp;

	tmp = *data->lines;
	while (tmp != NULL)
	{
		free(tmp);
		data->lines++;
		tmp = *data->lines;
	}
}
