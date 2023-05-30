/*
** EPITECH PROJECT, 2023
** cpu_class.c
** File description:
** CPU oop definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    CPUClass *self = (CPUClass *) ptr;

    if (!((self->context = malloc(sizeof(*self->context))))) {
        HANDLE_ERROR("failed memory allocation");
    }
    my_memset(self->context, 0, sizeof(*self->context));
    self->parent = va_arg(*args, WarriorClass *);
}

static void destructor(void *ptr)
{
    CPUClass *self = (CPUClass *) ptr;
    free(self->context);
}

const CPUClass init_cpu = {
    {
        ._size = sizeof(CPUClass),
        ._name = "CPU",
        ._constructor = constructor,
        ._destructor = destructor,
    },
    .register_lookup =
        {
            RT_NONE,
            RT_1,
            RT_2,
            RT_3,
            RT_4,
            RT_5,
            RT_6,
            RT_7,
            RT_8,
            RT_9,
            RT_10,
            RT_11,
            RT_12,
            RT_13,
            RT_14,
            RT_15,
            RT_16,
            RT_C,
            RT_PC,
        },
    .fetch = cpu_fetch,
    .decode = cpu_decode,
    .execute = cpu_execute,
    .step = cpu_step,
    .parse = cpu_parse,
    .read_register = cpu_read_register,
    .write_register = cpu_write_register,
};

const class_t *CPU = (const class_t *) &init_cpu;
