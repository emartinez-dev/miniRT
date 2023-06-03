#include "engine.h"
#include "vec3.h"
#include <stdio.h>

double	radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	calculate_camera(t_camera *c)
{
	t_v3	horizontal_2;
	t_v3	vertical_2;

	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->viewport_height = 2 * tan(radians(c->h_fov / 2.0));
	c->viewport_width = c->viewport_height * c->aspect_ratio;
	c->horizontal = vec3_multk((t_v3){1, 0, 0}, c->viewport_width);
	c->vertical = vec3_multk((t_v3){0, 1, 0}, c->viewport_height);
	horizontal_2 = vec3_divk(c->horizontal, 2);
	vertical_2 = vec3_divk(c->vertical, 2);
	c->lower_left_corner = vec3_sub(vec3_sub(c->p, horizontal_2), vertical_2);
}
