#ifndef _VEHICLE_H_
#define _VEHICLE_H_

struct vehicle;

struct vehicle *vehicle_alloc(const char *plate);
void vehicle_free(struct vehicle *v);
void vehicle_init(struct vehicle *v, const char *plate);

void vehicle_set_plate(struct vehicle *v, const char *plate);
const char *vehicle_get_plate(const struct vehicle *v);

void vehicle_print(const struct vehicle *v);

#endif
