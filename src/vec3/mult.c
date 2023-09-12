/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mult.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:33:55 by franmart          #+#    #+#             */
/*   Updated: 2023/09/12 13:33:56 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_v3	vec3_multv(t_v3 v1, t_v3 v2)
{
	t_v3	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

t_v3	vec3_multk(t_v3 v, double k)
{
	t_v3	result;

	result.x = v.x * k;
	result.y = v.y * k;
	result.z = v.z * k;
	return (result);
}

double	vec3_dot(t_v3 v1, t_v3 v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
}

t_v3	vec3_cross(t_v3 v1, t_v3 v2)
{
	t_v3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

t_v3	vec3_mulm(t_v3 v, t_m4 mt)
{
	t_v3	r;

	r.x = v.x * mt.m[0][0] + v.y * mt.m[0][1] + v.z * mt.m[0][2] + mt.m[0][3];
	r.y = v.x * mt.m[1][0] + v.y * mt.m[1][1] + v.z * mt.m[1][2] + mt.m[1][3];
	r.z = v.x * mt.m[2][0] + v.y * mt.m[2][1] + v.z * mt.m[2][2] + mt.m[2][3];
	return (r);
}
