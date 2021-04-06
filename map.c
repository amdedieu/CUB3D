#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct s_list // voir libft
{
	void * content;
	struct s_list * next;
}				t_list;

typedef struct s_pos // Equivalent au sprite
{
	int x;
	int y;
}				t_pos;

void lst_add_back(t_list **list, t_list * elem) // voir libft
{
	t_list *tmp = *list;

	if (tmp == NULL)
	{
		*list = elem;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}

void print_all_pos(t_list **list)
{
	t_list *elem = *list;

	while (elem)
	{
		// Cast content en pos pour pouvoir le manipuler
		t_pos * pos = (t_pos *)elem->content;
		printf("pos : %d, %d\n", pos->x, pos->y);
		// Allez au prochain elem
		elem = elem->next;
	}
}

// *list = element
// **list = pointer sur un element
int get_sprite(char *line, )
{
	t_list **list;
	t_list *new_elem;
	t_pos	*pos;
	// initie la liste chainée
	list = malloc(sizeof(t_list *));

	for (int i = 0; i < 10; ++i)
	{
		// Complete la struture pos
		pos = malloc(sizeof(t_pos));
		pos->x = i;
		pos->y = i * 2;
		// Envoie la pos dans new_elem sous void *
		new_elem = lst_new((void *)pos);
		// Ajoute new elem dans la list
		lst_add_back(list, new_elem);
	}

	print_all_pos(list);

	return 0;
}
