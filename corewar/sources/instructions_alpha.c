/*
** EPITECH PROJECT, 2023
** instructions_alpha.c
** File description:
** Instructions alpha methods
*/

#include "../include/corewar.h"

void proc_live(CPUClass *cpu)
{
    FAST_PRINT("The player %d(%s)is alive.\n",
        cpu->context->fetched_data.param_1, cpu->parent->rom->data->name);
    cpu->parent->context->alive_cycle = cpu->parent->context->cycle;
    cpu->parent->parent->live_count += 1;
    cpu->parent->cycles(cpu->parent, 10);
}

void proc_ld(CPUClass *cpu)
{
    uint16_t data = cpu->context->fetched_data.param_1;
    uint8_t value = cpu->context->registers.pc - 3 + data % IDX_MOD;
    register_type_t reg = cpu->context->fetched_data.param_2;

    cpu->write_register(cpu, reg, value);
    cpu->context->registers.c = value == 0;
    cpu->parent->cycles(cpu->parent, 5);
}

void proc_st(CPUClass *cpu)
{
    register_type_t reg = cpu->context->fetched_data.param_1;
    int32_t value = cpu->read_register(cpu, reg);
    uint16_t address = cpu->context->registers.pc
        + ((cpu->context->fetched_data.param_2 % MAX_MEMORY) % IDX_MOD)
        - ST_ARGS;

    cpu->parent->cycles(cpu->parent, 5);
    switch (cpu->context->fetched_data.byte_2) {
        case CB_REGISTER:
            cpu->write_register(
                cpu, cpu->context->fetched_data.param_2, value);
            break;
        case CB_INDIRECT:
            for (int8_t i = 0; i < 4; i++) {
                cpu->parent->bus->write(cpu->parent->bus, address + i,
                    (value >> (8 * (3 - i))) & 0xFF);
            }
            break;
        default: HANDLE_ERROR("invalid coding byte");
    }
}

void proc_add(CPUClass *cpu)
{
    register_type_t reg_1 = cpu->context->fetched_data.param_1;
    register_type_t reg_2 = cpu->context->fetched_data.param_2;
    register_type_t reg_3 = cpu->context->fetched_data.param_3;
    int32_t value_1 = cpu->read_register(cpu, reg_1);
    int32_t value_2 = cpu->read_register(cpu, reg_2);
    int32_t result = value_1 + value_2;

    cpu->write_register(cpu, reg_3, result);
    cpu->context->registers.c = result == 0;
    cpu->parent->cycles(cpu->parent, 10);
}

void proc_sub(CPUClass *cpu)
{
    register_type_t reg_1 = cpu->context->fetched_data.param_1;
    register_type_t reg_2 = cpu->context->fetched_data.param_2;
    register_type_t reg_3 = cpu->context->fetched_data.param_3;
    int32_t value_1 = cpu->read_register(cpu, reg_1);
    int32_t value_2 = cpu->read_register(cpu, reg_2);
    int32_t result = value_1 - value_2;

    cpu->write_register(cpu, reg_3, result);
    cpu->context->registers.c = result == 0;
    cpu->parent->cycles(cpu->parent, 10);
}
