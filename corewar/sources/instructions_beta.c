/*
** EPITECH PROJECT, 2023
** instructions_beta.c
** File description:
** Instructions beta methods
*/

#include "../include/corewar.h"

void proc_and(CPUClass *cpu)
{
    int32_t result = cpu->context->fetched_data.param_1
        & cpu->context->fetched_data.param_2;
    register_type_t reg = cpu->context->fetched_data.param_3;

    cpu->write_register(cpu, reg, result);
    cpu->context->registers.c = result == 0;
    cpu->parent->cycles(cpu->parent, 6);
}

void proc_or(CPUClass *cpu)
{
    int32_t result = cpu->context->fetched_data.param_1
        | cpu->context->fetched_data.param_2;
    register_type_t reg = cpu->context->fetched_data.param_3;

    cpu->write_register(cpu, reg, result);
    cpu->context->registers.c = result == 0;
    cpu->parent->cycles(cpu->parent, 6);
}

void proc_xor(CPUClass *cpu)
{
    int32_t result = cpu->context->fetched_data.param_1
        ^ cpu->context->fetched_data.param_2;
    register_type_t reg = cpu->context->fetched_data.param_3;

    cpu->write_register(cpu, reg, result);
    cpu->context->registers.c = result == 0;
    cpu->parent->cycles(cpu->parent, 6);
}

void proc_zjmp(CPUClass *cpu)
{
    uint16_t data = cpu->context->fetched_data.param_1;

    if (cpu->context->registers.c) {
        cpu->context->registers.pc =
            ((cpu->context->registers.pc + data) % MAX_MEMORY) % IDX_MOD
            - ZJMP_ARGS;
    }
    cpu->parent->cycles(cpu->parent, 20);
}

void proc_ldi(CPUClass *cpu)
{
    int16_t data = 0, value = 0;
    int16_t offset = cpu->context->fetched_data.param_1;
    int16_t address =
        (cpu->context->registers.pc + offset % MAX_MEMORY) % IDX_MOD
        - LDI_ARGS;

    for (int8_t i = 1; i >= 0; i--) {
        uint8_t byte = cpu->parent->bus->read(cpu->parent->bus, address++);
        data |= ((int16_t) byte << (i * 8));
    }
    data += cpu->context->fetched_data.param_2;
    value = cpu->parent->bus->read(cpu->parent->bus,
        (cpu->context->registers.pc + data % MAX_MEMORY) % IDX_MOD - LDI_ARGS);
    cpu->write_register(cpu, cpu->context->fetched_data.param_3, value);
    cpu->context->registers.c = (value == 0);
    cpu->parent->cycles(cpu->parent, 25);
}
