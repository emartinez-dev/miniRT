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
