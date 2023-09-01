#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 1400
# define HEIGHT 1000
# define EPSILON 0.000001

//	Materials	//

# define AMBIENT 1.0
# define DIFFUSE 1.0
# define SPECULAR 1.0
# define SHININESS 32.0

/*	EXAMPLE METAL  */
/*
# define AMBIENT 0.2
# define DIFFUSE 0.7
# define SPECULAR 0.5
# define SHININESS 32.0
*/
/*	EXAMPLE  PLASTIC */
/*
# define AMBIENT 0.1
# define DIFFUSE 0.8
# define SPECULAR 0.3
# define SHININESS 16.0
*/

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

typedef struct s_phong
{
	t_hit	*hit;
	t_ray	shadow;
	t_color	color;
	t_color	color_light;
	double	dot;
	double	intensity;
	t_v3	p;
}	t_phong;

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

/*	phong.c	*/
t_color			phong_light(t_scene *scene, t_hit *hit);

/* maths.c */
int				solve_quadratic(t_quadratic *q);
int				max(int a, int b);
int				min(int a, int b);
double			to_radians(double degrees);

/* hooks.c */
void			key_hook(void *mlx);
int				resize_image(t_window *w, mlx_image_t *src);
void			resize_hook(int32_t width, int32_t height, void *window);

/* light_utils.c */
void			normalize_intensity(t_list *lights);
int				is_in_shadow(t_scene *scene, t_phong *ph);
int				is_at_back(t_phong *ph);

#endif
