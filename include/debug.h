/*
** EPITECH PROJECT, 2023
** debug.h
** File description:
** CPU header entrypoint
*/

#include "common.h"
#include "oop.h"

#ifndef __DEBUG
    #define __DEBUG

typedef struct warrior_aux WarriorClass;
typedef struct debug_aux DebugClass;

typedef struct debug_aux {
    /* Properties */
    class_t metadata;
    WarriorClass *parent;
    /* Methods */
    void (*prettify)(DebugClass *, char *, int64_t);
    void (*print)(DebugClass *, int32_t);
    void (*get_registers)(DebugClass *, char *);
} DebugClass;

extern const class_t *Debug;

void debug_print(DebugClass *, int32_t);
void debug_prettify(DebugClass *, char *, int64_t);
void debug_get_registers(DebugClass *, char *);
#endif
