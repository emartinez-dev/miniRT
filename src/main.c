#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "MLX42.h"
#include <stdio.h>
#include <limits.h>
#include "vec3.h"

/*void	ft_leaks(void)
{
	system("leaks -q miniRT");
}*/

static void	manage_window(t_scene *scene, t_window *w);

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_window	window;

//	atexit(ft_leaks);
	if (params_error(argc, argv, &scene))
		return (1);
	read_scene(&scene);
	if (extract_objects(&scene) != 0)
	{
		ft_printf("\nThe provided scene: %s is bad formed\n\n", argv[1]);
		free_scene(&scene);
		return (1);
	}
	manage_window(&scene, &window);
	if (window.mlx)
		mlx_terminate(window.mlx);
	free_scene(&scene);
	return (0);
}

static void	manage_window(t_scene *scene, t_window *w)
{
	w->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!w->mlx)
		return ;
	mlx_get_monitor_size(0, &w->m_width, &w->m_height);
	if (!w->m_width || !w->m_height)
	{
		ft_printf("\nNo monitor detected\n");
		w->m_width = WIDTH;
		w->m_height = HEIGHT;
	}
	w->origin_img = mlx_new_image(w->mlx, w->m_width, w->m_height);
	if (!w->origin_img)
		return ;
	camera_init(scene->camera, w);
	print_todo(scene);
	render(w, scene);
	mlx_key_hook(w->mlx, &key_hook, &w);
	mlx_resize_hook(w->mlx, &resize_hook, &w);
	mlx_loop(w->mlx);
}
