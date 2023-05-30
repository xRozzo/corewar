/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main corewar entry point
*/

#include "../include/corewar.h"

#ifndef __COREWAR_TEST
int main(int argc, char **argv)
{
    uint8_t error = 0;
    CoreWarClass *self = new_class(CoreWar, argc, argv, MAX_WARRIORS);

    self->run(self);
    error = self->errored;
    destroy_class(self);
    return error;
}
#endif
