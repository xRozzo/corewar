/*
** EPITECH PROJECT, 2023
** cpu_core.c
** File description:
** CPU core methods
*/

#include "../include/corewar.h"

void cpu_fetch(CPUClass *self)
{
    self->context->op_code = self->parent->bus->read(
        self->parent->bus, self->context->registers.pc++);
    if (self->context->op_code > _IN_COUNT)
        HANDLE_ERROR("Invalid op code");
    self->context->instr = self->parent->instructions->by_opcode(
        self->parent->instructions, self->context->op_code);
    switch (self->context->instr->type) {
        case IN_LIVE:
        case IN_ZJMP:
        case IN_FORK:
        case IN_LFORK: break;
        default:
            self->context->instr->byte.raw = self->parent->bus->read(
                self->parent->bus, self->context->registers.pc++);
    }
}

void cpu_decode(CPUClass *self)
{
    if (self->context->instr == NULL) {
        return;
    }
    switch (self->context->instr->type) {
        case IN_LIVE:
        case IN_ZJMP:
        case IN_FORK:
        case IN_LFORK: {
            self->parse(self, CB_DIRECT, &self->context->fetched_data.param_1);
            break;
        }
        default:
            self->parse(self, self->context->instr->byte.param_1,
                &self->context->fetched_data.param_1);
            self->parse(self, self->context->instr->byte.param_2,
                &self->context->fetched_data.param_2);
            self->parse(self, self->context->instr->byte.param_3,
                &self->context->fetched_data.param_3);
    }
}

bool cpu_step(CPUClass *self)
{
    self->fetch(self);
    self->decode(self);
    if (self->context->instr == NULL) {
        HANDLE_ERROR("invalid instruction");
    }
    self->execute(self);
    return true;
}

int32_t cpu_read_register(CPUClass *self, register_type_t reg)
{
    if (reg >= _RT_COUNT || reg <= RT_NONE) {
        HANDLE_ERROR("invalid register read");
    }
    if (reg == RT_C) {
        return self->context->registers.c;
    }
    if (reg == RT_PC) {
        HANDLE_ERROR("cannot write to the program counter");
    }
    int64_t offset = offsetof(registers_t, r1) + (reg - 1) * sizeof(int32_t);
    return *(int32_t *) ((char *) &self->context->registers + offset);
}

void cpu_write_register(CPUClass *self, register_type_t reg, int32_t value)
{
    if (reg >= _RT_COUNT || reg <= RT_NONE) {
        HANDLE_ERROR("invalid register read");
    }
    if (reg == RT_C) {
        self->context->registers.c = value;
    }
    if (reg == RT_PC) {
        HANDLE_ERROR("cannot write to the program counter");
    }
    int64_t offset = offsetof(registers_t, r1) + (reg - 1) * sizeof(int32_t);
    *(int32_t *) ((char *) &self->context->registers + offset) = value;
}
