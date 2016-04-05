#include "list.h"
#include <stdio.h>

struct E {
	int a;
	struct list_head lh;
};

int main()
{
	struct list_head list;
	struct E e1, e2, *e;

	INIT_LIST_HEAD(&list);

	list_add(&(e1.lh), &list);
	list_add(&(e2.lh), &list);

	list_for_each_entry(e, &list, lh)
		printf("%d\n", e->a);

	return 0;
}
