/*
** EPITECH PROJECT, 2023
** rom_class.c
** File description:
** ROM oop definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    ROMClass *self = (ROMClass *) ptr;

    if (!((self->context = malloc(sizeof(*self->context))))) {
        HANDLE_ERROR("failed memory allocation");
    }
    my_memset(self->context, 0, sizeof(*self->context));
    self->parent = va_arg(*args, WarriorClass *);
    self->context->memory = va_arg(*args, uint8_t *);
}

static void destructor(void *ptr)
{
    ROMClass *self = (ROMClass *) ptr;
    free(self->context);
    free(self->data);
}

const ROMClass init_rom = {
    {
        ._size = sizeof(ROMClass),
        ._name = "ROM",
        ._constructor = constructor,
        ._destructor = destructor,
    },
    .load = rom_load,
    .read = rom_read,
    .write = rom_write,
};

const class_t *ROM = (const class_t *)&init_rom;
