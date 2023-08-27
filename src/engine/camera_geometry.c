#include "vec3.h"
#include "engine.h"
#include <stdio.h>

/* the look_at variable is the initial arbitrary position we give to our camera,
in this case I put it looking towards positive Z. As cross between the normal of
the camera and our orientation can't be parallel, I added an if for corner
cases

the camera works as the following:
	- It starts looking at the positive Z axis, but if the camera is already
		looking at the positive Z axis, it will look at the positive X axis.
	- The up vector is the cross between the Z axis and the normal of the
		camera, so it will always be perpendicular to the camera. (pointing up)
	- The front vector is the cross between the up vector and the normal of the
		camera, so it will always be perpendicular to the camera and the up
		vector. (pointing to the front)
*/
void	camera_init(t_camera *c)
{
	t_v3	look_at;
	t_v3	right;
	t_v3	up;

	c->norm = vec3_normalize(c->norm);
	look_at = (t_v3){0, 0, 1};
	if (c->norm.z == 1 || c->norm.z == -1)
		look_at = (t_v3){-c->norm.z, 0, 0};
	look_at = vec3_normalize(look_at);
	up = vec3_cross(look_at, c->norm);
	up = vec3_normalize(up);
	right = vec3_cross(up, c->norm);
	right = vec3_normalize(right);
	init_rotation_camera(c, right, up);
	c->aspect_ratio = WIDTH / (double)HEIGHT;
	c->fov = tan(to_radians(c->h_fov) / 2.0);
}

t_v3	cam_direction(int x, int y, t_camera *c)
{
	double	w;
	double	h;

	w = (2 * ((x + 0.5) / WIDTH) - 1) * c->aspect_ratio * c->fov;
	h = (1 - 2 * ((y + 0.5) / HEIGHT)) * c->fov;
	return ((t_v3){w, h, 1});
}

t_ray	camera_ray(t_camera *c, int x, int y)
{
	t_ray	cam_ray;

	cam_ray.origin = c->p;
	cam_ray.direction = cam_direction(x, y, c);
	cam_ray.direction = vec3_mulm(cam_ray.direction, c->rotation);
	cam_ray.direction = vec3_sub(cam_ray.direction, cam_ray.origin);
	cam_ray.direction = vec3_normalize(cam_ray.direction);
	return (cam_ray);
}

/* the rotation-translation matrix is like this:

	| right.x		up.x		norm.x		p.x |
	| right.y		up.y		norm.y		p.y |
	| right.z		up.z		norm.z		p.z |
	| 0				0			0			1
*/
void	init_rotation_camera(t_camera *c, t_v3 right, t_v3 up)
{
	c->rotation.m[0][0] = right.x;
	c->rotation.m[1][0] = right.y;
	c->rotation.m[2][0] = right.z;
	c->rotation.m[3][0] = 0;
	c->rotation.m[0][1] = up.x;
	c->rotation.m[1][1] = up.y;
	c->rotation.m[2][1] = up.z;
	c->rotation.m[3][1] = 0;
	c->rotation.m[0][2] = c->norm.x;
	c->rotation.m[1][2] = c->norm.y;
	c->rotation.m[2][2] = c->norm.z;
	c->rotation.m[3][2] = 0;
	c->rotation.m[0][3] = c->p.x;
	c->rotation.m[1][3] = c->p.y;
	c->rotation.m[2][3] = c->p.z;
	c->rotation.m[3][3] = 1;
}
