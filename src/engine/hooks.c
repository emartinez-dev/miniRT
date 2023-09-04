#include "MLX42.h"
#include "MLX42_Int.h"
#include "engine.h"

void	key_hook(mlx_key_data_t keydata, void *window)
{
	t_window	**w;

	w = (t_window **)window;
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_S)
		{
			if ((*w)->smooth)
				(*w)->smooth = 0;
			else
				(*w)->smooth = 1;
			resize_image(*w, (*w)->origin_img);
		}
	}
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window((*w)->mlx);
	}
}

void	resize_hook(int32_t width, int32_t height, void *window)
{
	t_window	**win;

	win = (t_window **) window;
	(*win)->w_width = width;
	(*win)->w_height = height;
	if (!resize_image((*win), (*win)->origin_img))
		mlx_terminate((*win)->mlx);
}
