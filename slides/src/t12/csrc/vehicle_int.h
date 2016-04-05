#ifndef _VEHICLE_INT_
#define _VEHICLE_INT_

#include <stdint.h>

struct vehicle
{
	char *plate;

	void (*set_plate)(struct vehicle *, const char *);
	const char *(*get_plate)(const struct vehicle *);
	void (*print)(const struct vehicle *);

	uint32_t flags;
};

enum vehicle_attr {
	VEHICLE_PLATE,
};

#endif
