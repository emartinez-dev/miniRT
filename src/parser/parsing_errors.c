#include "parser.h"

/* If ft_strlen(ft_strnstr(filename, rt)) returns other than 3, then the file is
not a valid ".rt" (3 chars) file */

int	params_error(int argc, char **argv, t_scene *scene)
{
	int	fd;

	if (argc != 2)
	{
		ft_putstr_fd(ERROR_ARGC, STDERR_FILENO);
		return (1);
	}
	if (ft_strlen(ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))) != 3)
	{
		ft_putstr_fd(ERROR_ARGC, STDERR_FILENO);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERROR_FILE, STDERR_FILENO);
		return (1);
	}
	scene->fd = fd;
	return (0);
}
