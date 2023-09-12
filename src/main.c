#include "parser.h"
#include "engine.h"
#include "objects.h"
#include "MLX42.h"
#include <stdio.h>
#include <limits.h>
#include "vec3.h"

static void	manage_window(t_scene *scene, t_window *w);
static int	init_lights(t_scene *scene);
static int	check_lights(t_scene *scene);

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_window	window;

	if (params_error(argc, argv, &scene))
		return (1);
	read_scene(&scene);
	if (extract_objects(&scene) != 0)
	{
		ft_printf("Error\nThe provided scene: %s is bad formed\n\n", argv[1]);
		free_scene(&scene);
		return (1);
	}
	if (!init_lights(&scene))
	{
		ft_printf("%s%s%s", ERROR_LIGHT, ERROR_PARTIAL,
			"More than one light or ambient light\n\n");
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
	render(w, scene);
	mlx_loop_hook(w->mlx, key_hook, &(w->mlx));
	mlx_resize_hook(w->mlx, &resize_hook, &w);
	mlx_loop(w->mlx);
}

static int	init_lights(t_scene *scene)
{
	t_amb_light	*amb;
	t_light		*light;

	amb = scene->ambient_light;
	light = scene->light;
	amb->v_c = vec3_multk(vec3_divk(amb->v_c, 255), amb->ratio * AMBIENT);
	while (light)
	{
		if (BONUS)
			light->v_c = vec3_multk(vec3_divk(light->v_c, 255),
					light->brightness);
		else
			light->v_c = vec3_multk((t_v3){1, 1, 1}, light->brightness);
		light = light->next;
	}
	if (!BONUS)
		return (check_lights(scene));
	return (1);
}

static int	check_lights(t_scene *scene)
{
	t_list	*lights;
	int		count;

	lights = scene->lights;
	count = 0;
	while (lights)
	{
		count++;
		lights = lights->next;
	}
	if (count != 2)
		return (0);
	return (1);
}
