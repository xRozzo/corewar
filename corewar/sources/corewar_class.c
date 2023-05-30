/*
** EPITECH PROJECT, 2023
** corewar_class.c
** File description:
** CoreWar oop definitions
*/

#include "../include/corewar.h"

static void constructor(void *ptr, va_list *args)
{
    CoreWarClass *self = (CoreWarClass *) ptr;
    uint32_t argc = va_arg(*args, int32_t);
    char **argv = va_arg(*args, char **);
    int64_t warriors = va_arg(*args, int64_t);
    if (!((self->warrior_pool = malloc(warriors * sizeof(WarriorClass *)))))
        HANDLE_ERROR("failed memory allocation");
    self->max_warriors = warriors;
    self->parse_flags(self, argc, argv);
    WarriorClass *warrior = NULL;
    uint64_t offset = 0;
    for (int64_t i = 0; i < self->warrior_count; i++) {
        warrior = *(self->warrior_pool + i);
        offset = (MAX_MEMORY / self->warrior_count) * i;
        my_memcpy(self->memory + offset, warrior->rom->data->data,
            warrior->rom->data->size);
        warrior->rom->context->offset = offset;
    }
    self->alive_count = self->warrior_count;
}

static void destructor(void *ptr)
{
    CoreWarClass *self = (CoreWarClass *) ptr;
    for (int64_t i = 0; i < self->warrior_count; i++) {
        destroy_class(*(self->warrior_pool + i));
    }
    free(self->warrior_pool);
}

const CoreWarClass init_corewar = {
    {
        ._size = sizeof(CoreWarClass),
        ._name = "CoreWar",
        ._constructor = constructor,
        ._destructor = destructor,
    },
    .run = corewar_run,
    .dump = corewar_dump,
    .parse_flags = corewar_parse_flags,
    .check_alive = corewar_check_alive,
    .delta_cycles = MAX_CYCLES,
    .cycles = 0,
    .dump_cycle = -1,
};

const class_t *CoreWar = (const class_t *) &init_corewar;
