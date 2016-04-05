#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct element {
	int a;
	struct list_head list;
	int b;
};

struct element *element_alloc(int a, int b);

int main()
{
	struct list_head list;
	struct element *element;

	INIT_LIST_HEAD(&list);
	@\pause@
	element = element_alloc(1, 1);
	list_add(&(element->list), &list);
	@\pause@
	element = element_alloc(2, 2);
	list_add(&(element->list), &list);
	@\pause@
	list_for_each_entry(element, &list, list)
		printf("{%d, %d}\n", element->a, element->b);

	return 0;
}

struct element *element_alloc(int a, int b)
{
	struct element *e;

	e = (struct element *)malloc(sizeof(struct element));
	e->a = a;
	e->b = b;

	return e;
}
