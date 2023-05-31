#ifndef OBJECTS_H
# define OBJECTS_H

/* Abbreviatures used:
- t_point p -> coordinates in the plane
- t_point c -> color
- t_point norm -> 3D normalized orientation vector
*/

enum e_objects {
	OBJ_AMBIENT_LIGHT,
	OBJ_CAMERA,
	OBJ_LIGHT,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
};

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_object
{
	int		type;
	void	*ptr;
}	t_object;

typedef struct s_cylinder
{
	t_point	p;
	t_point	norm;
	t_color	c;
	double	diameter;
	double	height;
}	t_cylinder;

typedef struct s_sphere
{
	t_point	p;
	t_color	c;
	double	diameter;
}	t_sphere;

typedef struct s_plane
{
	t_point	p;
	t_point	norm;
	t_color	c;
}	t_plane;

typedef struct s_amb_light
{
	double	ratio;
	t_color	c;
}	t_amb_light;

typedef struct s_camera
{
	t_point			p;
	t_point			norm;
	unsigned char	fov;
}	t_camera;

typedef struct s_light
{
	t_point	p;
	double	brightness;
	t_point	c;
}	t_camera;

#endif
