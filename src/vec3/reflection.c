#include "vec3.h"

t_v3	vec3_reflection(t_v3 incident, t_v3 normal)
{
	t_v3	refelction;
	double	dot;

	dot = vec3_dot(incident, normal);
	refelction = vec3_sub(incident, (vec3_multk(normal, (2.0 * dot))));
	return (refelction);
}
