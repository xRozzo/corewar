/*
** EPITECH PROJECT, 2022
** oop.c
** File description:
** OOP methods
*/

#include "../include/corewar.h"

void *new_class(const class_t *self, ...)
{
    va_list ap;
    va_start(ap, self);
    void *class = allocate_class(self, &ap);
    return class;
}

void *allocate_class(const class_t *self, va_list *ap)
{
    if (self == NULL || self->_size < sizeof(*self)) {
        return NULL;
    }
    class_t *class = malloc(self->_size);
    if (class == NULL) {
        return class;
    }
    my_memcpy(class, self, self->_size);
    if (self->_constructor != NULL) {
        self->_constructor(class, ap);
    }
    return class;
}

void destroy_class(void *self)
{
    class_t *class = (class_t *) self;
    if (class != NULL && class->_destructor != NULL) {
        class->_destructor(class);
    }
    free(class);
}
