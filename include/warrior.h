/*
** EPITECH PROJECT, 2023
** warrior.h
** File description:
** Warrior header entrypoint
*/

#include "bus.h"
#include "common.h"
#include "cpu.h"
#include "debug.h"
#include "instructions.h"
#include "oop.h"
#include "rom.h"

#ifndef __WARRIOR
    #define __WARRIOR

typedef struct corewar_aux CoreWarClass;
typedef struct warrior_aux WarriorClass;

typedef struct warrior_aux {
    /* Metadata */
    class_t metadata;
    CPUClass *cpu;
    ROMClass *rom;
    InstructionsClass *instructions;
    BusClass *bus;
    DebugClass *debug;
    CoreWarClass *parent;
    warrior_context_t *context;
    /* Methods */
    void (*exec)(WarriorClass *, int64_t);
    void (*cycles)(WarriorClass *, int32_t);
} WarriorClass;

extern const class_t *Warrior;

void warrior_exec(WarriorClass *, int64_t);
void warrior_cycles(WarriorClass *, int32_t);
#endif
