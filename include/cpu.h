/*
** EPITECH PROJECT, 2023
** cpu.h
** File description:
** CPU header entrypoint
*/

#include "common.h"
#include "oop.h"

#ifndef __CPU
    #define __CPU

typedef struct warrior_aux WarriorClass;
typedef struct cpu_aux CPUClass;

typedef struct cpu_aux {
    /* Properties */
    class_t metadata;
    register_type_t register_lookup[_RT_COUNT];
    WarriorClass *parent;
    cpu_context_t *context;
    /* Methods */
    bool (*step)(CPUClass *);
    void (*fetch)(CPUClass *);
    void (*decode)(CPUClass *);
    void (*execute)(CPUClass *);
    void (*parse)(CPUClass *, coding_byte_t, int32_t *);
    int32_t (*read_register)(CPUClass *, register_type_t);
    void (*write_register)(CPUClass *, register_type_t, int32_t);
} CPUClass;

extern const class_t *CPU;

bool cpu_step(CPUClass *);
void cpu_fetch(CPUClass *);
void cpu_decode(CPUClass *);
void cpu_parse(CPUClass *, coding_byte_t, int32_t *);
void cpu_execute(CPUClass *);
int32_t cpu_read_register(CPUClass *, register_type_t);
void cpu_write_register(CPUClass *, register_type_t, int32_t);
#endif
