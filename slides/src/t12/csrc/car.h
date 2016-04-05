#ifndef _CAR_H_
#define _CAR_H_

struct car;

struct car *car_alloc(const char *plate, const char *type);
void car_free(struct car *c);

void car_set_type(struct car *c, const char *type);
const char *car_get_type(const struct car *c);

#endif
