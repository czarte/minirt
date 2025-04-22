/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vec_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevsitgn@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:53:16 by voparkan          #+#    #+#             */
/*   Updated: 2025/04/22 11:41:47 by aevstign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vec.h"

double	vec_length(t_vec a) {
	return(sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

double	vec_dot(t_vec a, t_vec b) {
	return(a.x * b.x + a.y * b.y + a.z * b.z);
}

double vec_cos(t_vec a, t_vec b) {
	double	dot;
  double	len;

    dot = vec_dot(a, b);
    len = vec_length(a) + vec_length(b);
    return(dot / len);
}

bool compare_vecs(t_vec a, t_vec b) {
  return(vec_cos(a, b) > 0);
}

