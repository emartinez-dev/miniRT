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

void	render(mlx_t *mlx, mlx_image_t *img, t_scene *scene)
{
	t_ray	ray;
	int		h;
	int		w;

	h = -1;
	while (++h < HEIGHT)
	{
		w = -1;
		while (++w < WIDTH)
		{
			ray = raycast(w, h, scene);
			mlx_put_pixel(img, w, h, rgb_to_hex(ray.color));
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	//atexit(ft_leaks);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (params_error(argc, argv, &scene))
		return (1);
	read_scene(&scene);
	if (extract_objects(&scene) != 0)
		ft_printf("\nThe provided scene: %s is bad formed\n\n", argv[1]);
	else
	{
		camera_init(scene.camera);
		print_todo(&scene);
		render(mlx, img, &scene);
	}
	mlx_loop(mlx);
	free_scene(&scene);
	return (0);
}
