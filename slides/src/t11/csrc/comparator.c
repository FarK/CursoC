#include <stdio.h>

struct obj {
	int a;
	int b;
};

int cmp_a(struct obj *a, struct obj *b)
{
	if (a->a > b->a)
		return 1;
	else if (a->a < b->a)
		return -1;
	else
		return 0;
}

int cmp_b(struct obj *a, struct obj *b)
{
	if (a->b > b->b)
		return 1;
	else if (a->b < b->b)
		return -1;
	else
		return 0;
}

void obj_print(const struct obj *o)
{
	printf("{%d, %d}\n", o->a, o->b);
}

typedef int (*ptrf_cmp_t)(struct obj *a, struct obj *b);

const struct obj *max(struct obj *a, struct obj *b,
                      ptrf_cmp_t cmpf)
{
	if (cmpf(a, b) > 0)
		return a;
	else
		return b;
}

int main()
{
	struct obj a = {1, 2};
	struct obj b = {2, 1};

	obj_print(max(&a, &b, cmp_a));
	obj_print(max(&a, &b, cmp_b));

	return 0;
}
