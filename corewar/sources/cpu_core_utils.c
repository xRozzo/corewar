/*
** EPITECH PROJECT, 2023
** cpu_core.c
** File description:
** CPU core methods
*/

#include "../include/corewar.h"

static void handle_direct_byte
(CPUClass *self, coding_byte_t byte, int32_t *target)
{
    int32_t out = 0;
    for (int8_t i = 3; i >= 0; i--) {
        uint8_t sub_byte = self->parent->bus->read(
                self->parent->bus, self->context->registers.pc++);
        out |= ((int32_t) sub_byte << (i * 8));
    }
    *target = (out);
    *(coding_byte_t *) (target + 1) = byte;
}

static void handle_indirect_byte
(CPUClass *self, coding_byte_t byte, int32_t *target)
{
    uint16_t out = 0;
    for (int8_t i = 1; i >= 0; i--) {
        uint8_t sub_byte = self->parent->bus->read(
                self->parent->bus, self->context->registers.pc++);
        out |= ((uint16_t) sub_byte << (i * 8));
    }
    *target = (out);
    *(coding_byte_t *) (target + 1) = byte;
}

static void handle_register_byte
(CPUClass *self, coding_byte_t byte, int32_t *target)
{
    *target = self->parent->bus->read(
            self->parent->bus, self->context->registers.pc++);
    *(coding_byte_t *) (target + 1) = byte;
}

void cpu_execute(CPUClass *self)
{
    proc_fn proc = self->parent->instructions->get_proc(
            self->parent->instructions, self->context->instr->type);
    if (!proc) {
        HANDLE_ERROR("instruction not yet implemented");
    }
    proc(self);
}

void cpu_parse(CPUClass *self, coding_byte_t byte, int32_t *target)
{
    if (byte == CB_DIRECT && self->context->instr->is_relative)
        byte = CB_INDIRECT;
    switch (byte) {
        case CB_NONE: break;
        case CB_DIRECT:
            handle_direct_byte(self, byte, target);
            break;
        case CB_INDIRECT:
            handle_indirect_byte(self, byte, target);
            break;
        case CB_REGISTER:
            handle_register_byte(self, byte, target);
            break;
    }
}
