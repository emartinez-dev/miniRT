#ifndef PARSER_H
# define PARSER_H

# ifndef BONUS
#  define BONUS 0
# endif

# include "libft.h"
# include <fcntl.h>
# include "get_next_line.h"
# include "fractol_utils.h"
# include "ft_printf.h"
# include "objects.h"
# include <math.h>
# include "MLX42.h"

# define ERROR_ARGC "Error\n[ERROR] invalid input.\n\tUsage: ./miniRT [filename].rt\n"
# define ERROR_EXT "Error\n[ERROR] invalid scene. File format must be .rt\n"
# define ERROR_FILE "Error\n[ERROR] invalid file. Please check that file exists\n"

typedef struct s_scene
{
	int			fd;
	char		**scene_str;
	int			errors;
	t_list		*objects;
	t_list		*lights;
	t_light		*light;
	t_amb_light	*ambient_light;
	t_camera	*camera;
}	t_scene;

/* OBJECTS */

void		get_lights(t_scene *scene);
t_object	*parse_obj_ambient_light(char *line);
int			errors_ambient_light(t_amb_light *light, t_object *obj);

t_object	*parse_obj_camera(char *line);
int			errors_camera(t_camera *camera, t_object *obj);
t_camera	*get_camera(t_list *obj);
t_list		*remove_camera_from_list(t_list *head);

t_object	*parse_obj_cylinder(char *line);
int			errors_cylinder(t_cylinder *cylinder, t_object *obj);

t_object	*parse_obj_light(char *line);
int			errors_light(t_light *light, t_object *obj);

t_object	*parse_obj_plane(char *line);
int			errors_plane(t_plane *plane, t_object *obj);

t_object	*parse_obj_sphere(char *line);
int			errors_sphere(t_sphere *sphere, t_object *obj);

/* coordinates.c */
void		get_xyz(char *str, t_v3 *point, t_object *obj);

/* colors.c */
void		get_color(char *str, t_color *color);
void		color_to_vec(t_color *color, t_v3 *v_c);
t_color		vec_to_color(t_v3 v_c);

/* parser_utils.c */
char		*replace_tabs(char *str);
int			matrix_len(char **str);
void		free_matrix(char **str);

/* parser_frees.c */
void		free_objects(void *content);
void		free_scene(t_scene *scene);

/* parser_errors.c */
int			params_error(int argc, char **argv, t_scene *scene);
int			errors_normalized_vector(t_v3 *norm);
int			errors_colors(t_color *color);
int			errors_in_objects(t_scene *scene);
int			invalid_line(t_scene *scene);

/* parser_scene.c */
void		read_scene(t_scene *scene);
void		*parse_line(char *line, int lights);
int			extract_objects(t_scene *scene);
t_list		*parse_all_lights(t_scene *scene);
t_list		*parse_all_objects(t_scene *scene);

/* pruebas.c */
void		print_todo(t_scene *scene);
void		print_vector(t_v3 v);

#endif
