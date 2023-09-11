#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 1400
# define HEIGHT 1000
# define EPSILON 0.000001

# define AMBIENT 1.0
# define DIFFUSE 1.0
# define SPECULAR 1.0 
# define SHININESS 50.0

# include "objects.h"
# include "parser.h"
# include "libft.h"
# include "MLX42.h"
# include "vec3.h"
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
	double		t;
	t_object	*object;
	t_color		color;
	t_v3		view;
}	t_hit;

typedef struct s_quadratic {
	double	a;
	double	b;
	double	half_b;
	double	c;
	double	t;
	double	discriminant;
	double	t1;
	double	t2;
	t_v3	oc;
	double	delta;
	double	y0;
	double	y1;
	t_v3	normal;
}	t_quadratic;

typedef struct s_window
{
	mlx_t		*mlx;
	mlx_image_t	*origin_img;
	mlx_image_t	*render_img;
	int			m_width;
	int			m_height;
	uint32_t	w_width;
	uint32_t	w_height;
	uint32_t	n_width;
	uint32_t	n_height;
	double		w_step;
	double		h_step;
	double		step;
	int			pos_x;
	int			pos_y;
}	t_window;

/* colors.c */
unsigned int	rgb_to_hex(t_color color);
t_color			clamp_colors(t_color color);
t_color			color_sum(t_color color0, t_color color2);
t_color			color_norm(t_color color1);

/* camera_geometry.c */
void			init_rotation_camera(t_camera *c, t_v3 right, t_v3 up);
void			camera_init(t_camera *c, t_window *w);
t_v3			cam_direction(int x, int y, t_camera *c, t_window *win);
t_ray			camera_ray(t_camera *c, int x, int y, t_window *w);

/* rays.c */
//void			render(mlx_t *mlx, mlx_image_t *img, t_scene *scene);
void			render(t_window *w, t_scene *scene);
t_ray			raycast(double u, double v, t_scene *scene, t_window *w);
t_color			raycolor(t_ray ray, t_hit *hit, t_scene *scene);
t_v3			ray_at(t_ray *ray, double t);

/* object intersections */
t_hit			hit_objects(t_ray *ray, t_list *objects);
t_hit			hit_sphere(t_sphere *sp, t_ray ray, t_hit hit);
t_hit			hit_plane(t_plane *pl, t_ray ray, t_hit hit);
t_hit			hit_cylinder(t_cylinder *cyl, t_ray ray, t_hit hit);
double			intersect_plane(t_ray ray, t_v3 norm, t_v3 p);
int				intersect_circle(t_ray *ray, t_circle *circle);

/*	phong.c	*/
t_color			phong_light(t_scene *scene, t_hit *hit, t_color ambient);
t_color			apply_light(t_color color_obj, t_v3 color_light,
					double intensity);

/* maths.c */
int				solve_quadratic(t_quadratic *q);
int				max(int a, int b);
int				min(int a, int b);
double			to_radians(double degrees);

/* hooks.c */
void			key_hook(void *mlx);
int				resize_image(t_window *w, mlx_image_t *src);
void			resize_hook(int32_t width, int32_t height, void *window);

#endif
