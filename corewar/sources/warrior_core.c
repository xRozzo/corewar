/*
** EPITECH PROJECT, 2023
** warrior_core.c
** File description:
** Warrior core methods
*/

#include "../include/corewar.h"

void warrior_exec(WarriorClass *self, int64_t cycle)
{
    if (self->context->running && self->context->cycle == cycle) {
        self->cpu->fetch(self->cpu);
        self->cpu->decode(self->cpu);
        if (self->cpu->context->instr == NULL) {
            HANDLE_ERROR("invalid instruction");
        }
        self->context->next_cycle =
            cycle + self->cpu->context->instr->cycles - 1;
        return;
    }

    if (self->context->running && self->context->next_cycle == cycle) {
        self->cpu->execute(self->cpu);
#ifdef __DEV
        self->debug->print(self->debug, self->cpu->context->registers.pc);
#endif
    }
}

void warrior_cycles(WarriorClass *self, int32_t cycles)
{
    self->context->cycle += cycles;
}
