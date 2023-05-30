/*
** EPITECH PROJECT, 2023
** instructions_gamma.c
** File description:
** Instructions gamma methods
*/

#include "../include/corewar.h"

void proc_sti(CPUClass *cpu)
{
    register_type_t reg = cpu->context->fetched_data.param_1;
    int16_t index_1 = cpu->context->fetched_data.param_2;
    int16_t index_2 = cpu->context->fetched_data.param_3;
    int32_t value = cpu->read_register(cpu, reg);
    int16_t address =
        (cpu->context->registers.pc - 4 + (index_1 + index_2) % MAX_MEMORY)
        % IDX_MOD;

    for (int8_t i = 0; i < 4; i++) {
        cpu->parent->bus->write(
            cpu->parent->bus, address - i, (value >> (8 * i)) & 0xFF);
    }
    cpu->parent->cycles(cpu->parent, 25);
}

void proc_fork(CPUClass *cpu)
{
    uint16_t address = cpu->context->registers.pc - 3
        + cpu->context->fetched_data.param_1 % IDX_MOD;
    WarriorClass *warrior = new_class(Warrior,
        ++cpu->parent->parent->warrior_index, cpu->parent->parent->memory,
        cpu->parent->parent, cpu->parent->rom->context->path);

    my_memcpy(warrior->cpu->context, cpu->context, sizeof(*cpu->context));
    warrior->cpu->context->registers.pc = address;
    warrior->context->uuid = cpu->parent->context->uuid;

    *(cpu->parent->parent->warrior_pool + cpu->parent->parent->warrior_count) =
        warrior;
    cpu->parent->parent->warrior_count += 1;
    cpu->parent->cycles(cpu->parent, 800);

    warrior->context->next_cycle = cpu->parent->context->cycle + 1;
    warrior->context->cycle = cpu->parent->context->cycle;
}

void proc_lld(CPUClass UNUSED *cpu)
{
    uint16_t data = cpu->context->fetched_data.param_1;
    uint8_t value = cpu->parent->bus->read(cpu->parent->bus,
        ((cpu->context->registers.pc + data) % MAX_MEMORY) - LD_ARGS);
    register_type_t reg = cpu->context->fetched_data.param_2;

    cpu->write_register(cpu, reg, value);
    cpu->context->registers.c = value == 0;
    cpu->parent->cycles(cpu->parent, 10);
}

void proc_lldi(CPUClass UNUSED *cpu)
{
    int16_t data = 0, value = 0;
    int16_t offset = cpu->context->fetched_data.param_1;
    int16_t address =
        (cpu->context->registers.pc + offset % MAX_MEMORY) - LDI_ARGS;

    for (int8_t i = 1; i >= 0; i--) {
        uint8_t byte = cpu->parent->bus->read(cpu->parent->bus, address++);
        data |= ((int16_t) byte << (i * 8));
    }
    data += cpu->context->fetched_data.param_2;
    value = cpu->parent->bus->read(cpu->parent->bus,
        (cpu->context->registers.pc + data % MAX_MEMORY) - LDI_ARGS);
    cpu->write_register(cpu, cpu->context->fetched_data.param_3, value);
    cpu->context->registers.c = (value == 0);
    cpu->parent->cycles(cpu->parent, 50);
}

void proc_lfork(CPUClass UNUSED *cpu)
{
    HANDLE_ERROR("long fork not implemented");
    cpu->parent->cycles(cpu->parent, 1000);
}
