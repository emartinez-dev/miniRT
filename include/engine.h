#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 1400
# define HEIGHT 1000

# include "objects.h"
# include "parser.h"

typedef struct s_ray {
	t_v3	origin;
	t_v3	direction;
	t_color	color;
}	t_ray;

/* colors.c */
unsigned int	rgb_to_hex(t_color color);

/* camera_geometry.c */
void			calculate_camera(t_camera *c);

/* rays.c */
t_ray			raycast(t_v3 origin, double u, double v, t_scene *scene);
t_color			raycolor(t_ray ray, t_scene *scene);

int				hit_sphere(t_sphere *sp, t_ray ray);


#endif