#include <stdio.h>

struct gtype {
	int type;

	union {
		char char_t;
		int int_t;
		float float_t;
	};
};

int main()
{
	struct gtype gt;

	gt.int_t = 3;
	gt.type = 1;

	switch (gt.type) {
	case 0:
		printf("%c\n", gt.char_t);
		break;
	case 1:
		printf("%d\n", gt.int_t);
		break;
	case 2:
		printf("%f\n", gt.float_t);
		break;
	default:
		printf("error: invalid type\n");
		break;
	};

	return 0;
}
