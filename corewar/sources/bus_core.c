/*
** EPITECH PROJECT, 2023
** bus_core.c
** File description:
** Bus core methods
*/

#include "../include/corewar.h"

uint8_t bus_read(BusClass *self, uint16_t address)
{
    switch (address) {
        case 0x0 ... MAX_MEMORY: {
            return self->parent->rom->read(self->parent->rom, address);
        }
        default: HANDLE_ERROR("Out of bounds read");
    }
}

void bus_write(BusClass *self, uint16_t address, uint8_t value)
{
    switch (address) {
        case 0x0 ... MAX_MEMORY: {
            self->parent->rom->write(self->parent->rom, address, value);
            break;
        }
        default: HANDLE_ERROR("Out of bounds read");
    }
}
