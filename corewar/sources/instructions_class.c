/*
** EPITECH PROJECT, 2023
** instructions_class.c
** File description:
** Instructions oop definitions
*/

#include "../include/corewar.h"

const InstructionsClass init_instructions = {
    {
        ._size = sizeof(InstructionsClass),
        ._name = "Instructions",
        ._constructor = NULL,
        ._destructor = NULL,
    },
    .instructions =
        {
            [0x00] =
                {
                    .type = IN_NONE,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 0,
                },
            [0x01] =
                {
                    .type = IN_LIVE,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 10,
                },
            [0x02] =
                {
                    .type = IN_LD,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 5,
                },
            [0x03] =
                {
                    .type = IN_ST,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 5,
                },
            [0x04] =
                {
                    .type = IN_ADD,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 10,
                },
            [0x05] =
                {
                    .type = IN_SUB,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 10,
                },
            [0x06] =
                {
                    .type = IN_AND,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 6,
                },
            [0x07] =
                {
                    .type = IN_OR,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 6,
                },
            [0x08] =
                {
                    .type = IN_XOR,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 6,
                },
            [0x09] =
                {
                    .type = IN_ZJMP,
                    .condition = CT_C,
                    .byte = {.raw = 0},
                    .is_relative = true,
                    .cycles = 20,
                },
            [0x0A] =
                {
                    .type = IN_LDI,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = true,
                    .cycles = 25,
                },
            [0x0B] =
                {
                    .type = IN_STI,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = true,
                    .cycles = 25,
                },
            [0x0C] =
                {
                    .type = IN_FORK,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = true,
                    .cycles = 800,
                },
            [0x0D] =
                {
                    .type = IN_LLD,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 10,
                },
            [0x0E] =
                {
                    .type = IN_LLDI,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 50,
                },
            [0x0F] =
                {
                    .type = IN_LFORK,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 1000,
                },
            [0x10] =
                {
                    .type = IN_AFF,
                    .condition = CT_NONE,
                    .byte = {.raw = 0},
                    .is_relative = false,
                    .cycles = 2,
                },
        },
    .lookup_table =
        {
            "NONE",
            "LIVE",
            "LD",
            "ST",
            "ADD",
            "SUB",
            "AND",
            "OR",
            "XOR",
            "ZJMP",
            "LDI",
            "STI",
            "FORK",
            "LLD",
            "LLDI",
            "LFORK",
            "AFF",
        },
    .processors =
        {
            [IN_NONE] = proc_none,
            [IN_LIVE] = proc_live,
            [IN_LD] = proc_ld,
            [IN_ST] = proc_st,
            [IN_ADD] = proc_add,
            [IN_SUB] = proc_sub,
            [IN_AND] = proc_and,
            [IN_OR] = proc_or,
            [IN_XOR] = proc_xor,
            [IN_ZJMP] = proc_zjmp,
            [IN_LDI] = proc_ldi,
            [IN_STI] = proc_sti,
            [IN_FORK] = proc_fork,
            [IN_LLD] = proc_lld,
            [IN_LLDI] = proc_lldi,
            [IN_LFORK] = proc_lfork,
            [IN_AFF] = proc_aff,
        },
    .by_opcode = instructions_by_opcode,
    .lookup = instructions_lookup,
    .get_proc = instructions_get_proc,
};

const class_t *Instructions = (const class_t *) &init_instructions;
