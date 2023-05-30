/*
** EPITECH PROJECT, 2023
** rom.h
** File description:
** ROM header entrypoint
*/

#include "common.h"
#include "oop.h"

#ifndef __ROM
    #define __ROM

typedef struct warrior_aux WarriorClass;
typedef struct rom_aux ROMClass;

typedef struct rom_aux {
    /* Properties */
    class_t metadata;
    rom_data_t *data;
    WarriorClass *parent;
    rom_context_t *context;
    /* Methods */
    bool (*load)(ROMClass *, char *);
    uint8_t (*read)(ROMClass *, uint16_t);
    void (*write)(ROMClass *, uint16_t, uint8_t);
} ROMClass;

extern const class_t *ROM;

bool rom_load(ROMClass *, char *);
uint8_t rom_read(ROMClass *, uint16_t);
void rom_write(ROMClass *, uint16_t, uint8_t);
#endif
