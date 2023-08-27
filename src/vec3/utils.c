#include "vec3.h"

t_v3	vec3_negative(t_v3 v)
{
	t_v3	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}

double	vec3_sqlen(t_v3 v)
{
	double	result;

	result = v.x * v.x + v.y * v.y + v.z * v.z;
	return (result);
}

double	vec3_len(t_v3 v)
{
	double	result;

	result = sqrt(vec3_sqlen(v));
	return (result);
}

t_v3	vec3_normalize(t_v3 v)
{
	t_v3	result;
	double	len;

	len = vec3_len(v);
	result = vec3_divk(v, len);
	return (result);
}

double	vec3_distance(t_v3 v1, t_v3 v2)
{
	t_v3	result;
	double	dist;

	result = vec3_sub(v1, v2);
	dist = vec3_len(result);
	return (dist);
}
