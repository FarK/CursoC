#include "vehicle.h"
#include "car.h"

int main()
{
	struct vehicle *v;
	struct vehicle *c;

	v = vehicle_alloc("1234 ABC");
	c = (struct vehicle *)car_alloc("4321 CBA", "pickup");

	vehicle_print(v);
	vehicle_print(c);

	return 0;
};
