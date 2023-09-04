#include "MLX42.h"
#include "MLX42_Int.h"
#include "engine.h"

static void		fill_pixels(t_window *win, uint32_t *src, uint32_t *dst);
static void		smooth_image(t_window *win);
static t_color	smooth_pixel(uint32_t h, uint32_t w, t_window *win);

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
	{
		printf("Smoothing\n");
		smooth_image(win);
	}
}

static void	smooth_image(t_window *win)
{
	int			h;
	int			w;
	mlx_image_t	*dst;

	dst = mlx_new_image(win->mlx, win->n_width, win->n_height);
	h = -1;
	while (++h < (int)win->n_height)
	{
		w = -1;
		while (++w < (int)win->n_width)
			mlx_put_pixel(dst, w, h, rgb_to_hex(smooth_pixel(h, w, win)));
	}
	mlx_delete_image(win->mlx, win->render_img);
	win->render_img = dst;
}

static t_color	smooth_pixel(uint32_t h, uint32_t w, t_window *win)
{
	t_color		c;
	t_color		base;
	uint32_t	*src;

	src = (uint32_t *)win->render_img->pixels;
	base = hex_to_rgb((uint32_t)(src[(uint32_t)(h * win->n_width) + w]));
	c = base;
	if (w == 0)
		c = color_sum(c, base);
	else
		c = color_sum(c, hex_to_rgb(src[(uint32_t)(h * win->n_width) + w - 1]));
	if (w == win->n_width - 1)
		c = color_sum(c, base);
	else
		c = color_sum(c, hex_to_rgb(src[(uint32_t)(h * win->n_width) + w + 1]));
	if (h == 0)
		c = color_sum(c, base);
	else
		c = color_sum(c, hex_to_rgb(src[(uint32_t)((h - 1) * win->n_width) + w]));
	if (h == win->n_height - 1)
		c = color_sum(c, base);
	else
		c = color_sum(c, hex_to_rgb(src[(uint32_t)((h + 1) * win->n_width) + w]));
	return (color_div(c, 5));
}
