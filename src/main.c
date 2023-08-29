#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "MLX42.h"
#include <stdio.h>
#include <limits.h>
#include "vec3.h"

/* void	ft_leaks(void)
{
	system("leaks -q miniRT");
}
 */

static void manage_window(t_scene *scene);


int	main(int argc, char **argv)
{
	t_scene		scene;

	//atexit(ft_leaks);
	if (params_error(argc, argv, &scene))
		return (1);
	read_scene(&scene);
	if (extract_objects(&scene) != 0)
	{
		ft_printf("\nThe provided scene: %s is bad formed\n\n", argv[1]);
		free_scene(&scene);
		return (1);
	}
	manage_window(&scene);
	free_scene(&scene);
	return (0);
}

static void manage_window(t_scene *scene)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return ;
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	camera_init(scene->camera);
	print_todo(scene);
	render(mlx, img, scene);
	mlx_loop_hook(mlx, key_hook, &mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
