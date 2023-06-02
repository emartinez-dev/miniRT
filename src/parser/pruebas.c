#include "parser.h"
#include <stdio.h>

void	print_color(t_color color)
{
	printf("r:%d g:%d b:%d\n", color.r, color.g, color.b);
}

void	print_point(t_v3 p)
{
	printf("x:%f y:%f z:%f\n", p.x, p.y, p.z);
}

void	print_plane(void *ptr)
{
	t_plane	*pl;

	pl = ptr;
	print_color(pl->c);
	print_point(pl->p);
	print_point(pl->norm);
}

void	print_camera(void *ptr)
{
	t_camera	*cam;

	cam = ptr;
	printf("-------------------------------\n");
	printf("---------   Camera   ----------\n");
	printf("-------------------------------\n");
	printf("fov: %d\n", cam->fov);
	print_point(cam->p);
	print_point(cam->norm);
}

void	print_sphere(void *ptr)
{
	t_sphere	*sphere;

	sphere = ptr;
	print_color(sphere->c);
	print_point(sphere->p);
	printf("diameter: %f\n", sphere->diameter);
}

void	print_cylinder(void *ptr)
{
	t_cylinder	*cylinder;

	cylinder = ptr;
	print_color(cylinder->c);
	print_point(cylinder->p);
	print_point(cylinder->norm);
	printf("diameter: %f\n", cylinder->diameter);
	printf("height: %f\n", cylinder->height);
}

void	print_amb_light(void *ptr)
{
	t_amb_light	*amb_light;

	amb_light = ptr;
	print_color(amb_light->c);
	printf("ratio: %f\n", amb_light->ratio);
}

void	print_light(void *ptr)
{
	t_light	*light;

	light = ptr;
	print_color(light->c);
	print_point(light->p);
	printf("brightness: %f\n", light->brightness);
}

void	print_todo(t_scene *scene)
{
	t_list		*head;
	t_object	*obj;
	char	*str[6];

	str[0] = "ambient light";
	str[1] = "camera";
	str[2] = "light";
	str[3] = "sphere";
	str[4] = "plane";
	str[5] = "cylinder";
	head = scene->objects;
	while (head)
	{
		obj = head->content;
		printf("-------------------------------\n");
		printf("Obj type: %s\n", str[obj->type]);
		printf("-------------------------------\n");
		if (obj->type == OBJ_PLANE)
			print_plane(obj->ptr);
		if (obj->type == OBJ_SPHERE)
			print_sphere(obj->ptr);
		if (obj->type == OBJ_CYLINDER)
			print_cylinder(obj->ptr);
		printf("\n\n");
		head = head->next;
	}
	head = scene->lights;
	while (head)
	{
		obj = head->content;
		printf("-------------------------------\n");
		printf("Obj type: %s\n", str[obj->type]);
		printf("-------------------------------\n");
		if (obj->type == OBJ_LIGHT)
			print_light(obj->ptr);
		if (obj->type == OBJ_AMBIENT_LIGHT)
			print_amb_light(obj->ptr);
		printf("\n\n");
		head = head->next;
	}
	if (scene->camera)
		print_camera(scene->camera);
}

void	print_vector(t_v3 v)
{
	printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
}
