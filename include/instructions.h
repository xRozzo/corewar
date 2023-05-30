/*
** EPITECH PROJECT, 2023
** instructions.h
** File description:
** Instructions header entrypoint
*/

#include "common.h"
#include "oop.h"

#ifndef __INSTRUCTIONS
    #define __INSTRUCTIONS

typedef struct instructions_aux InstructionsClass;

typedef struct instructions_aux {
    /* Properties */
    class_t metadata;
    char *lookup_table[_IN_COUNT];
    instruction_t instructions[_IN_COUNT];
    proc_fn processors[_IN_COUNT];
    /* Methods */
    instruction_t *(*by_opcode)(InstructionsClass *, uint8_t);
    proc_fn (*get_proc)(InstructionsClass *, instruction_type_t);
    char *(*lookup)(InstructionsClass *, instruction_type_t);
} InstructionsClass;

extern const class_t *Instructions;

instruction_t *instructions_by_opcode(InstructionsClass *, uint8_t);
char *instructions_lookup(InstructionsClass *, instruction_type_t);
proc_fn instructions_get_proc(InstructionsClass *, instruction_type_t);

void proc_none(CPUClass *);
void proc_live(CPUClass *);
void proc_ld(CPUClass *);
void proc_st(CPUClass *);
void proc_add(CPUClass *);
void proc_sub(CPUClass *);
void proc_and(CPUClass *);
void proc_or(CPUClass *);
void proc_xor(CPUClass *);
void proc_zjmp(CPUClass *);
void proc_ldi(CPUClass *);
void proc_sti(CPUClass *);
void proc_fork(CPUClass *);
void proc_lld(CPUClass *);
void proc_lldi(CPUClass *);
void proc_lfork(CPUClass *);
void proc_aff(CPUClass *);
#endif
