/*
** EPITECH PROJECT, 2023
** bus_class.c
** File description:
** Bus oop definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    BusClass *self = (BusClass *) ptr;
    self->parent = va_arg(*args, WarriorClass *);
}

const BusClass init_bus = {
    {
        ._size = sizeof(BusClass),
        ._name = "Bus",
        ._constructor = constructor,
        ._destructor = NULL,
    },
    .read = bus_read,
    .write = bus_write,
};

const class_t *Bus = (const class_t *) &init_bus;
