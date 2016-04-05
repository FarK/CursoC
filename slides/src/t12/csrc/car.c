#include "car.h"
#include "vehicle.h"
#include "vehicle_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ATTR_SET(flags, attr)    (flags) |= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))

struct car {
	struct vehicle super; /* Siempre el primero */
	char *type;
	uint32_t flags;
};

enum car_attr {
	CAR_TYPE,
};

static void car_printf(const struct vehicle *v);

struct car *car_alloc(const char *plate, const char *type)
{
	struct car *c;

	c = (struct car *)malloc(sizeof(struct car));
	if (!c)
		return NULL;

	vehicle_init(&c->super, plate);

	c->flags = 0;
	c->super.print = car_printf;
	car_set_type(c, type);

	return c;
}

void car_free(struct car *c)
{
	if (ATTR_IS_SET(c->flags, CAR_TYPE))
		free(c->type);
	vehicle_free(&c->super);
}


const char *car_get_type(const struct car *c)
{
	if (ATTR_IS_SET(c->flags, CAR_TYPE))
		return c->type;
	return NULL;
}

void car_set_type(struct car *c, const char *type)
{
	if (ATTR_IS_SET(c->flags, CAR_TYPE))
		free(c->type);
	c->type = strdup(type);
	ATTR_SET(c->flags, CAR_TYPE);
}

static void car_printf(const struct vehicle *v)
{
	struct car *c = (struct car *)v;

	printf("Car {");

	if (ATTR_IS_SET(v->flags, VEHICLE_PLATE))
		printf("\n\tplate = \"%s\"", v->plate);

	if (ATTR_IS_SET(c->flags, CAR_TYPE))
		printf("\n\ttype = \"%s\"", c->type);

	printf("\n}\n");
}
