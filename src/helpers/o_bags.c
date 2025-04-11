/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_bags.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: voparkan <voparkan@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:19:11 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/11 17:19:11 by voparkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	do_j_bzero(t_obag *ob)
{
	ob->j = 0;
	bzero(ob->buf, 1024);
}

void	init_tobag(t_obag *obag)
{
	if (obag == NULL)
		perror("unable to allocate memory for the obag");
	obag->spl_buf = NULL;
	obag->k = 0;
	obag->i = 1;
	obag->j = 0;
}

void	move_cp_buf(char *tmp, t_obag *ob)
{
	while (ft_spacious(tmp[ob->i]))
		ob->i++;
	while (tmp[ob->i] && !ft_spacious(tmp[ob->i]))
		ob->buf[ob->j++] = tmp[ob->i++];
	ob->buf[ob->i] = '\0';
}
