#include "MLX42.h"

void	key_hook(void *mlx)
{
	mlx_t	**mlx_;

	mlx_ = (mlx_t **) mlx;
	if (mlx_is_key_down(*mlx_, MLX_KEY_ESCAPE))
		mlx_close_window(*mlx_);
}
