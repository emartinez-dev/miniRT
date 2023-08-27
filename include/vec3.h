#ifndef VEC3_H
# define VEC3_H

# include "objects.h"
# include <math.h>

/* mult.c */

/* Multiply two vectors */
t_v3	vec3_multv(t_v3 v1, t_v3 v2);

/* Multiply vector by a scalar */
t_v3	vec3_multk(t_v3 v, double k);

/* Dot product of two vectors */
double	vec3_dot(t_v3 v1, t_v3 v2);

/* Cross product of two vectors */
t_v3	vec3_cross(t_v3 v1, t_v3 v2);

t_v3	vec3_mulm(t_v3 v, t_m4 mt);

/* div.c */

/* Divide v1 by v2 */
t_v3	vec3_divv(t_v3 v1, t_v3 v2);

/* Divide v by an scalar */
t_v3	vec3_divk(t_v3 v, double k);

/* sub.c */

/* Subtract v2 to v1 */
t_v3	vec3_sub(t_v3 v1, t_v3 v2);

/* sum.c */

/* Sum v2 to v1 */
t_v3	vec3_sum(t_v3 v1, t_v3 v2);

/* utils.c */

/* returns the negative of the vector */
t_v3	vec3_negative(t_v3 v);

/* returns the squared lenght of the vector */
double	vec3_sqlen(t_v3 v);

/* returns the lenght of the vector */
double	vec3_len(t_v3 v);

/* returns the unit vector of v */
t_v3	vec3_normalize(t_v3 v);

/* returns the distance between two vectors */
double	vec3_distance(t_v3 v1, t_v3 v2);

#endif
