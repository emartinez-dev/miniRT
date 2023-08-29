#include "MLX42.h"
#include "MLX42_Int.h"
#include "engine.h"

static void	fill_pixels(t_window *win, uint32_t *src, uint32_t *dst);

void	key_hook(void *mlx)
{
	mlx_t	**mlx_;

	mlx_ = (mlx_t **) mlx;
	if (mlx_is_key_down(*mlx_, MLX_KEY_ESCAPE))
		mlx_close_window(*mlx_);
}

int	resize_image(t_window *w, mlx_image_t *src)
{
	MLX_NONNULL(w->mlx);
	if (w->render_img)
		mlx_delete_image(w->mlx, w->render_img);
	if (w->w_width != src->width || w->w_height != src->height)
	{
		w->render_img = mlx_new_image(w->mlx, w->w_width, w->w_height);
		w->w_step = (double)src->width / w->w_width;
		w->h_step = (double)src->height / w->w_height;
		fill_pixels(w, (uint32_t *)src->pixels,
			(uint32_t *)w->render_img->pixels);
	}
	return (1);
}

static void	fill_pixels(t_window *win, uint32_t *src, uint32_t *dst)
{
	int	h;
	int	w;
	int	nw;
	int	nh;

	nw = win->w_width;
	nh = win->w_height;
	h = -1;
	while (++h < nh)
	{
		w = -1;
		while (++w < nw)
			dst[h * nw + w] = src[(uint32_t)(h * win->h_step)
				* win->origin_img->width + (uint32_t)(w * win->w_step)];
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
	mlx_image_to_window((*win)->mlx, (*win)->render_img, 0, 0);
}
