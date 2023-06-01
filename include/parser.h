#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <fcntl.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "objects.h"

# define ERROR_ARGC "[ERROR] invalid input.\n\tUsage: ./miniRT [filename].rt\n"
# define ERROR_EXT "[ERROR] invalid scene. File format must be .rt\n"
# define ERROR_FILE "[ERROR] invalid file. Please check that file exists\n"

typedef struct s_scene
{
	int		fd;
	char	**scene_str;
	t_list	*objects;
	t_list	*lights;
}	t_scene;

/* parsing_errors.c */
int			params_error(int argc, char **argv, t_scene *scene);
int			errors_normalized_vector(t_point *norm);
int			errors_colors(t_color *color);

/* scene_reading.c */
void		read_scene(t_scene *scene);
void		*parse_line(char *line);
int			extract_objects(t_scene *scene);
t_list		*parse_all_lights(t_scene *scene);
t_list		*parse_all_objects(t_scene *scene);

/* ambient_lights.c */
t_object	*parse_obj_ambient_light(char *line);
int			errors_ambient_light(t_amb_light *light, t_object *obj);

/* camera.c */
t_object	*parse_obj_camera(char *line);
int			errors_camera(t_camera *camera, t_object *obj);

/* coordnates.c */
void		get_xyz(char *str, t_point *point, t_object *obj);

/* colors.c */
void		get_color(char *str, t_color *color);

/* parser_utils.c */
double		ft_atod(char *str);
double		decimal_part(char *str);
int			matrix_len(char **str);
void		free_matrix(char **str);

/* parser_frees.c */
void		free_objects(void *content);
void		free_scene(t_scene *scene);

/* pruebas.c */
void		print_todo(t_scene *scene);

#endif