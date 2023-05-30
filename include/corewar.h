/*
** EPITECH PROJECT, 2023
** corewar.h
** File description:
** Main header entrypoint
*/

#include "oop.h"
#include "warrior.h"

#ifndef __COREWAR
    #define __COREWAR

typedef struct corewar_aux CoreWarClass;

typedef struct corewar_aux {
    /* Metadata */
    class_t metadata;
    bool errored;
    int64_t cycles;
    uint16_t delta_cycles;
    int64_t warrior_count;
    int64_t max_warriors;
    int64_t alive_count;
    int64_t live_count;
    int64_t dump_cycle;
    WarriorClass **warrior_pool;
    bool checked[MAX_WARRIORS];
    uint8_t memory[MAX_MEMORY];
    uint64_t warrior_index;
    /* Methods */
    void (*run)(CoreWarClass *);
    void (*dump)(CoreWarClass *);
    void (*parse_flags)(CoreWarClass *, int32_t, char **);
    bool (*check_alive)(CoreWarClass *);
} CoreWarClass;

extern const class_t *CoreWar;

void corewar_run(CoreWarClass *);
void corewar_dump(CoreWarClass *);
void corewar_parse_flags(CoreWarClass *, int32_t, char **);
bool corewar_check_alive(CoreWarClass *);
#endif
