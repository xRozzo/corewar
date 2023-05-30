/*
** EPITECH PROJECT, 2023
** debug_class.c
** File description:
** Debug core methods
*/

#include "../include/corewar.h"

void debug_print(DebugClass *self, int32_t pc)
{
    char buff[256] = {0}, disasm[64] = {0}, regs[96 + 1] = {0};
    self->prettify(self, disasm, sizeof(disasm));
    self->get_registers(self, regs);

    int32_t len =
        mini_sprintf(buff, "%d %08lX - %04X: %-4s %-14s %d (%02X)\n%s\n",
            self->parent->context->uuid, self->parent->context->cycle, pc,
            self->parent->instructions->lookup(self->parent->instructions,
                self->parent->cpu->context->instr->type),
            disasm, self->parent->cpu->context->registers.c,
            self->parent->cpu->context->op_code, regs);

    write(STDERR_FILENO, buff, len);
}

void debug_prettify(DebugClass *self, char *buffer, int64_t UNUSED size)
{
    switch (self->parent->cpu->context->instr->type) {
        case IN_AFF: case IN_FORK: case IN_LFORK: case IN_ZJMP: case IN_LIVE:
            mini_sprintf(buffer, "%04X",
                self->parent->cpu->context->fetched_data.param_1);
            break;
        case IN_LLD: case IN_LLDI: case IN_LD: case IN_ST:
            mini_sprintf(buffer, "%04X,%04X",
                self->parent->cpu->context->fetched_data.param_1,
                self->parent->cpu->context->fetched_data.param_2);
            break;
        case IN_ADD: case IN_SUB:
        case IN_AND: case IN_OR: case IN_XOR: case IN_LDI: case IN_STI:
            mini_sprintf(buffer, "%04X,%04X,%04X",
                self->parent->cpu->context->fetched_data.param_1,
                self->parent->cpu->context->fetched_data.param_2,
                self->parent->cpu->context->fetched_data.param_3);
            break;
        default: break;
    }
}

void debug_get_registers(DebugClass *self, char *buffer)
{
    for (register_type_t reg = RT_1; reg <= RT_16; reg++) {
        int32_t value = cpu_read_register(self->parent->cpu, reg);
        char value_str[12];

        mini_sprintf(value_str, "%04X", value);
        my_strcat(buffer, value_str);

        if (reg != RT_16) {
            my_strcat(buffer, "-");
        }
    }
}
