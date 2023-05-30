/*
** EPITECH PROJECT, 2023
** bus.h
** File description:
** Bus header entrypoint
*/

#include "common.h"
#include "oop.h"

#ifndef __BUS
    #define __BUS

typedef struct warrior_aux WarriorClass;
typedef struct bus_aux BusClass;

typedef struct bus_aux {
    /* Properties */
    class_t metadata;
    WarriorClass *parent;
    /* Methods */
    uint8_t (*read)(BusClass *, uint16_t);
    void (*write)(BusClass *, uint16_t, uint8_t);
} BusClass;

extern const class_t *Bus;

uint8_t bus_read(BusClass *, uint16_t);
void bus_write(BusClass *, uint16_t, uint8_t);
#endif
