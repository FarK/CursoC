#include "vehicle.h"
#include "vehicle_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ATTR_SET(flags, attr)    (flags) |= (1 << (attr))
#define ATTR_IS_SET(flags, attr) ((flags) & (1 << (attr)))


static void default_set_plate(struct vehicle *v, const char *plate);
static const char *default_get_plate(const struct vehicle *v);
static void default_print(const struct vehicle *v);

void vehicle_init(struct vehicle *v, const char *plate)
{
	v->flags = 0;

	v->set_plate = default_set_plate;
	v->get_plate = default_get_plate;
	v->print = default_print;

	default_set_plate(v, plate);
}

struct vehicle *vehicle_alloc(const char *plate)
{
	struct vehicle *v;

	v = (struct vehicle *)malloc(sizeof(struct vehicle));
	if (!v)
		return NULL;

	vehicle_init(v, plate);

	return v;
}

void vehicle_free(struct vehicle *v)
{
	if (ATTR_IS_SET(v->flags, VEHICLE_PLATE))
		free(v->plate);

	free(v);
}

static void default_set_plate(struct vehicle *v, const char *plate)
{
	if (ATTR_IS_SET(v->flags, VEHICLE_PLATE))
		free(v->plate);
	v->plate = strdup(plate);
	ATTR_SET(v->flags, VEHICLE_PLATE);
}

static const char *default_get_plate(const struct vehicle *v)
{
	if (ATTR_IS_SET(v->flags, VEHICLE_PLATE))
		return v->plate;
	return NULL;
}

static void default_print(const struct vehicle *v)
{
	printf("Vehicle {");

	if (ATTR_IS_SET(v->flags, VEHICLE_PLATE))
		printf("\n\tplate = \"%s\"", v->plate);

	printf("\n}\n");
}

void vehicle_set_plate(struct vehicle *v, const char *plate)
{
	v->set_plate(v, plate);
}

const char *vehicle_get_plate(const struct vehicle *v)
{
	return v->get_plate(v);
}

void vehicle_print(const struct vehicle *v)
{
	v->print(v);
}
