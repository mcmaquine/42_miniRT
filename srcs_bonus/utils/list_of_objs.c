#include "minirt_bonus.h"

t_list	*list_of_objs(t_list *objs[])
{
	t_list	*head;
	t_list	*last;

	if (objs[0])
		head = objs[0];
	else
		return (objs[2]);
	last = ft_lstlast(head);
	if (objs[2])
		last->next = objs[2];
	return (head);
}
