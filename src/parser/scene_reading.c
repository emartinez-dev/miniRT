#include "parser.h"

void	read_scene(t_scene *scene)
{
	char	*buffer;
	char	*line;
	char	*tmp;

	buffer = ft_calloc(1, sizeof(char));
	buffer[0] = '\0';
	line = get_next_line(scene->fd);
	while (line)
	{
		tmp = ft_strjoin(buffer, line);
		free(buffer);
		free(line);
		buffer = tmp;
		line = get_next_line(scene->fd);
	}
	scene->scene_str = ft_split(buffer, '\n');
	free(buffer);
}

void	free_scene(t_scene *scene)
{
	int	i;

	i = -1;
	while (scene->scene_str[++i])
	{
		ft_printf("%s\n", scene->scene_str[i]);
		free(scene->scene_str[i]);
	}
	free(scene->scene_str);
}
