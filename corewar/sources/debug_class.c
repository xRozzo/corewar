/*
** EPITECH PROJECT, 2023
** debug_class.c
** File description:
** Debug OOP definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    DebugClass *self = (DebugClass *) ptr;
    self->parent = va_arg(*args, WarriorClass *);
}

const DebugClass init_debug = {
    {
        ._size = sizeof(DebugClass),
        ._name = "Debug",
        ._constructor = constructor,
        ._destructor = NULL,
    },
    .print = debug_print,
    .prettify = debug_prettify,
    .get_registers = debug_get_registers,
};

const class_t *Debug = (const class_t *) &init_debug;
