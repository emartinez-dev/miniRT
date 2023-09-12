/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:47:49 by juan-aga          #+#    #+#             */
/*   Updated: 2023/09/12 14:47:51 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int	solve_quadratic(t_quadratic *q)
{
	double	x;

	q->discriminant = q->b * q->b - 4 * q->a * q->c;
	if (q->discriminant < 0)
		return (0);
	if (q->discriminant == 0)
	{
		q->t1 = -0.5 * q->b / q->a;
		q->t2 = q->t1;
	}
	else
	{
		if (q->b > 0)
			x = -0.5 * (q->b + sqrt(q->discriminant));
		else
			x = -0.5 * (q->b - sqrt(q->discriminant));
		q->t1 = x / q->a;
		q->t2 = q->c / x;
	}
	return (1);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}
