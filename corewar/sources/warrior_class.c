/*
** EPITECH PROJECT, 2023
** warrior_class.c
** File description:
** Warrior oop definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    WarriorClass *self = (WarriorClass *) ptr;

    if (!((self->context = malloc(sizeof(*self->context))))) {
        HANDLE_ERROR("failed memory allocation");
    }
    my_memset(self->context, 0, sizeof(*self->context));
    self->context->uuid = va_arg(*args, int64_t);
    self->cpu = new_class(CPU, self);
    self->rom = new_class(ROM, self, va_arg(*args, uint8_t *));
    self->bus = new_class(Bus, self);
    self->instructions = new_class(Instructions);
    self->parent = va_arg(*args, CoreWarClass *);
    self->cpu->context->registers.r1 = self->context->uuid;
    self->context->running = self->rom->load(
        self->rom, ((self->context->path = va_arg(*args, char *))));
}

static void destructor(void *ptr)
{
    WarriorClass *self = (WarriorClass *) ptr;
    destroy_class(self->cpu);
    destroy_class(self->rom);
    destroy_class(self->bus);
    destroy_class(self->instructions);
    free(self->context);
}

const WarriorClass init_warrior = {
    {
        ._size = sizeof(WarriorClass),
        ._name = "Warrior",
        ._constructor = constructor,
        ._destructor = destructor,
    },
    .exec = warrior_exec,
    .cycles = warrior_cycles,
};

const class_t *Warrior = (const class_t *) &init_warrior;
