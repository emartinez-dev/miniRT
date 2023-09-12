/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:33:59 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:33:59 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_v3	vec3_reflection(t_v3 incident, t_v3 normal)
{
	t_v3	refelction;
	double	dot;

	dot = vec3_dot(incident, normal);
	refelction = vec3_sub(incident, (vec3_multk(normal, (2.0 * dot))));
	return (refelction);
}
