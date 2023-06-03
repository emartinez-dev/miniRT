#ifndef ENGINE_H
# define ENGINE_H

# define WIDTH 1400
# define HEIGHT 1000

# include "objects.h"

/* colors.c */
unsigned int	rgb_to_hex(t_color color);

/* camera_geometry.c */
void			calculate_camera(t_camera *c);

#endif