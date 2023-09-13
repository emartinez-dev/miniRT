/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:33:53 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:33:54 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_v3	vec3_divv(t_v3 v1, t_v3 v2)
{
	t_v3	result;

	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	return (result);
}

t_v3	vec3_divk(t_v3 v, double k)
{
	t_v3	result;

	result.x = v.x / k;
	result.y = v.y / k;
	result.z = v.z / k;
	return (result);
}
