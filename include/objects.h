#ifndef OBJECTS_H
# define OBJECTS_H

/* Abbreviatures used:
- t_point p -> coordinates in the plane
- t_point c -> color
- t_point norm -> 3D normalized orientation vector
*/

# define ERR_RANGE "Values out of range\n"
# define ERR_MISSING_PARAMS "Insufficient parameters\n"

# define ERROR_AMBIENT_L "[AMBIENT_LIGHT_"
# define ERROR_CAMERA "[CAMERA_"
# define ERROR_LIGHT "[LIGHT_"
# define ERROR_SPHERE "[SPHERE_"
# define ERROR_PLANE "[PLANE_"
# define ERROR_CYLINDER "[CYLINDER_"
# define ERROR_PARTIAL "ERROR]\n"

enum e_objects {
	OBJ_AMBIENT_LIGHT,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
};

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}	t_v3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_object
{
	int		type;
	int		error;
	void	*ptr;
}	t_object;

typedef struct s_cylinder
{
	t_v3	p;
	t_v3	norm;
	t_color	c;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_sphere
{
	t_v3	p;
	t_color	c;
	double	diameter;
}	t_sphere;

typedef struct s_plane
{
	t_v3	p;
	t_v3	norm;
	t_color	c;
}	t_plane;

typedef struct s_amb_light
{
	double	ratio;
	t_color	c;
}	t_amb_light;

typedef struct s_camera
{
	t_v3	p;
	t_v3	norm;
	int		h_fov;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	t_v3	horizontal;
	t_v3	vertical;
	t_v3	lower_left_corner;
}	t_camera;

typedef struct s_light
{
	t_v3	p;
	double	brightness;
	t_color	c;
}	t_light;

#endif
