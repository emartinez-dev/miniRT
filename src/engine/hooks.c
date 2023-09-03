#include "MLX42.h"
#include "MLX42_Int.h"
#include "engine.h"

static void	fill_pixels(t_window *win, uint32_t *src, uint32_t *dst);

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

int	resize_image(t_window *w, mlx_image_t *src)
{
	if (w->render_img)
		mlx_delete_image(w->mlx, w->render_img);
	w->step = fmax((double)w->w_width / src->width,
			(double)w->w_height / src->height);
	w->n_width = src->width * w->step;
	w->n_height = src->height * w->step;
	w->render_img = mlx_new_image(w->mlx, w->n_width, w->n_height);
	if (!w->render_img)
		return (0);
	fill_pixels(w, (uint32_t *)src->pixels,
		(uint32_t *)w->render_img->pixels);
	w->pos_x = (int)(w->w_width - w->n_width) / 2;
	w->pos_y = (int)(w->w_height - w->n_height) / 2;
	mlx_image_to_window(w->mlx, w->render_img, w->pos_x, w->pos_y);
	return (1);
}

static void	fill_pixels(t_window *win, uint32_t *src, uint32_t *dst)
{
	int	h;
	int	w;
	int	nw;
	int	nh;

	nw = win->n_width;
	nh = win->n_height;
	h = -1;
	while (++h < nh)
	{
		w = -1;
		while (++w < nw)
			dst[h * nw + w] = src[(uint32_t)(h / win->step)
				* win->origin_img->width + (uint32_t)(w / win->step)];
	}
	if (win->smooth)
		printf("Smoothing\n");
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
