#include "parser.h"

void	get_xyz(char *str, t_point *point, t_object *obj)
{
	char	**split;

	split = ft_split(str, ',');
	if (matrix_len(split) == 3)
	{
		point->x = ft_atod(split[0]);
		point->y = ft_atod(split[1]);
		point->z = ft_atod(split[2]);
	}
	else
	{
		obj->error = 1;
		point->x = 0;
		point->y = 0;
		point->z = 0;
	}
	free_matrix(split);
}
