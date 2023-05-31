#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <fcntl.h>

# define ERROR_ARGC "[ERROR] invalid input.\n\tUsage: ./miniRT [filename].rt\n"
# define ERROR_EXT "[ERROR] invalid scene. File format must be .rt\n"
# define ERROR_FILE "[ERROR] invalid file. Please check that file exists\n"

typedef struct s_scene
{
	int	fd;
}	t_scene;

int	params_error(int argc, char **argv, t_scene *scene);

#endif