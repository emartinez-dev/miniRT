#include "MLX42.h"
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
	if (w->render_img)
		mlx_delete_image(w->mlx, w->render_img);
	w->w_step = (double)w->w_width / src->width;
	w->h_step = (double)w->w_height / src->height;
	w->step = fmax(w->w_step, w->h_step);
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
