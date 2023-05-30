/*
** EPITECH PROJECT, 2023
** corewar_core.c
** File description:
** CoreWar core methods
*/

#include "../include/corewar.h"

bool corewar_check_alive(CoreWarClass *self)
{
    WarriorClass *warrior = NULL;
    int64_t cycle_diff = 0;
    for (int64_t i = 0; i < self->warrior_count; i++) {
        if (self->live_count >= NBR_LIVE) {
            self->delta_cycles -= CYCLE_STEP;
            self->live_count = 0;
        }
        warrior = *(self->warrior_pool + i);
        cycle_diff = self->cycles - warrior->context->alive_cycle;
        if (self->cycles % self->delta_cycles == 0
            && *(self->checked + warrior->context->uuid) == false
            && cycle_diff > self->delta_cycles) {
            self->alive_count -= 1;
            warrior->context->running = false;
            return false;
        }
        *(self->checked + warrior->context->uuid) = true;
        warrior->exec(warrior, self->cycles);
    }
    return true;
}

void corewar_run(CoreWarClass *self)
{
    if (self->errored)
        return;
    for (self->cycles = 0; self->alive_count > 1; self->cycles++) {
        if (self->cycles == self->dump_cycle) {
            self->dump(self);
            return;
        }
        if (!self->check_alive(self))
            break;
        my_memset(self->checked, 0, MAX_WARRIORS);
    }
    for (int64_t i = 0; i < self->warrior_count; i++) {
        WarriorClass *warrior = *(self->warrior_pool + i);
        if (warrior->context->running) {
            (warrior->parent->dump_cycle >= 0) ? self->dump(self) : 1;
            FAST_PRINT("The player %d(%s)has won.\n", warrior->context->uuid,
                warrior->rom->data->name);
            break;
        }
    }
}

void corewar_dump(CoreWarClass *self)
{
    for (int16_t i = 0; i < MAX_MEMORY; i++) {
        if (i % 32 == 0) {
            FAST_PRINT("%-4X : ", i);
        }
        FAST_PRINT("%02X ", *(self->memory + i));
        if ((i + 1) % 32 == 0) {
            write(1, "\n", 1);
        }
    }
}

void corewar_parse_flags(CoreWarClass *self, int32_t argc, char **argv)
{
    for (int64_t i = 1; i < argc; i++) {
        self->warrior_index = self->warrior_count + 1;
        if (my_strcmp(*(argv + i), "-dump") == 0) {
            i = i + 1;
            self->dump_cycle = my_atoi(*(argv + i));
            continue;
        }
        if (my_strcmp(*(argv + i), "-n") == 0) {
            self->warrior_index = my_atoi(*(argv + i + 1));
            i = i + 2;
        }
        *(self->warrior_pool + self->warrior_count) = new_class(
            Warrior, self->warrior_index, self->memory, self, *(argv + i));
        self->warrior_count = self->warrior_count + 1;
    }
}
