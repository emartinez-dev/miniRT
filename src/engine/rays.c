/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-aga <juan_aga@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:48:09 by juan-aga          #+#    #+#             */
/*   Updated: 2023/09/12 14:48:12 by juan-aga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	render(t_window *win, t_scene *scene)

{
	int		h;
	int		w;
	t_ray	world_ray;

	h = -1;
	while (++h < win->m_height)
	{
		w = -1;
		while (++w < win->m_width)
		{
			world_ray = raycast(w, h, scene, win);
			mlx_put_pixel(win->origin_img, w, h, rgb_to_hex(world_ray.color));
		}
	}
	win->w_height = HEIGHT;
	win->w_width = WIDTH;
	win->render_img = NULL;
	if (!resize_image(win, win->origin_img))
		mlx_terminate(win->mlx);
}

t_ray	raycast(double u, double v, t_scene *scene, t_window *w)
{
	t_ray		cam_ray;
	t_hit		world_hit;

	cam_ray = camera_ray(scene->camera, u, v, w);
	world_hit = hit_objects(&cam_ray, scene->objects);
	cam_ray.color = raycolor(cam_ray, &world_hit, scene);
	return (cam_ray);
}

t_hit	hit_objects(t_ray *ray, t_list *objects)
{
	t_object	*o;
	t_hit		world;

	world.t = -1.0;
	while (objects)
	{
		o = (t_object *)objects->content;
		if (o->type == OBJ_SPHERE)
			world = hit_sphere((t_sphere *)o->ptr, *ray, world);
		else if (o->type == OBJ_PLANE)
			world = hit_plane((t_plane *)o->ptr, *ray, world);
		else if (o->type == OBJ_CYLINDER)
			world = hit_cylinder((t_cylinder *)o->ptr, *ray, world);
		objects = objects->next;
	}
	return (world);
}

/* this function returns the color of the object it hit or the "sky" color */
t_color	raycolor(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_v3		unit_direction;
	t_v3		c;
	t_color		color;
	double		t;

	color = apply_light(hit->color, scene->ambient_light->v_c, 1);
	if (hit->t > EPSILON)
		return (phong_light(scene, hit, color));
	unit_direction = vec3_normalize(ray.direction);
	t = 0.5 * (unit_direction.y + 1.0);
	c = vec3_sum(vec3_multk((t_v3){1.0, 1.0, 1.0}, 1.0 - t), \
		vec3_multk((t_v3){0.5, 0.7, 1.0}, t));
	c = vec3_multk(c, scene->ambient_light->ratio);
	color = (t_color){c.x * 255.999, c.y * 255.999, c.z * 255.999};
	return (color);
}

t_v3	ray_at(t_ray *ray, double t)
{
	t_v3	r;

	r = vec3_sum(ray->origin, vec3_multk(ray->direction, t));
	return (r);
}
