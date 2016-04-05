#ifndef _PERSON_H_
#define _PERSON_H_

struct person;

struct person *person_alloc();
void person_free(struct person *p);

/* Setters */
void person_set_name(struct person *p, const char *name);
int person_set_dni(struct person *p, const char *dni);
int person_set_age(struct person *p, int age);

/* Getters */
const char *person_get_name(const struct person *p);
const char *person_get_dni(const struct person *p);
int person_get_age(const struct person *p);

void person_print(const struct person *p);

#endif
