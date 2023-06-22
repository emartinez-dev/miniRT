#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 1400
# define HEIGHT 1000

# include "objects.h"
# include "parser.h"
# include <stdio.h>

typedef struct s_ray {
	t_v3	origin;
	t_v3	direction;
	t_color	color;
}	t_ray;

typedef struct s_hit
{
	t_v3		point;
	t_v3		normal;
	double		dist;
	double		t;
	t_object	*object;
}	t_hit;


/* colors.c */
unsigned int	rgb_to_hex(t_color color);
t_color			trim_colors(t_color	color);

/* camera_geometry.c */
void			calculate_camera(t_camera *c);

/* rays.c */
t_ray			raycast(t_v3 origin, double u, double v, t_scene *scene);
t_color			raycolor(t_ray ray, t_hit *hit, t_scene *scene);
t_v3			ray_at(t_ray *ray, double t);

void			hit_objects(t_ray ray, t_hit *hit, t_scene *scene);
void			hit_sphere(t_sphere *sp, t_ray ray, t_hit *hit, t_object *obj);
t_color			color_sphere(t_sphere *sp, t_scene *scene, t_ray *ray, \
						t_hit *hit);

#endif