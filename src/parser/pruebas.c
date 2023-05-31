#include "parser.h"

void	print_todo(t_scene *scene)
{
	t_list		*head;
	t_object	*obj;

	head = scene->objects;
	while (head)
	{
		obj = head->content;
		ft_printf("Obj type: %d\n", obj->type);
		head = head->next;
	}
	head = scene->lights;
	while (head)
	{
		obj = head->content;
		ft_printf("Light type: %d\n", obj->type);
		head = head->next;
	}
}
