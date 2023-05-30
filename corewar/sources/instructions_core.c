/*
** EPITECH PROJECT, 2023
** instructions_core.c
** File description:
** Instructions core methods
*/

#include "../include/corewar.h"

instruction_t *instructions_by_opcode(InstructionsClass *self, uint8_t op_code)
{
    return self->instructions + op_code;
}

char *instructions_lookup(InstructionsClass *self, instruction_type_t instr)
{
    return *(self->lookup_table + instr);
}

proc_fn instructions_get_proc(
    InstructionsClass *self, instruction_type_t instr)
{
    return *(self->processors + instr);
}

void proc_none(CPUClass UNUSED *cpu)
{
    HANDLE_ERROR("invalid instruction");
}

void proc_aff(CPUClass *cpu)
{
    register_type_t reg = cpu->context->fetched_data.param_1;
    char ch = cpu->read_register(cpu, reg) % 256;
    write(STDOUT_FILENO, &ch, 1);
    cpu->parent->cycles(cpu->parent, 2);
}
