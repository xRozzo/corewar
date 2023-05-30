/*
** EPITECH PROJECT, 2023
** rom_core.c
** File description:
** ROM core methods
*/

#include "../include/corewar.h"

bool rom_load(ROMClass *self, char *path)
{
    int64_t length = 0;
    FILE *fstream = fopen(path, "r");
    self->context->path = path;
    if (!fstream) {
        LOG("failed to open file");
        return !((self->parent->parent->errored = true));
    }
    fseek(fstream, 0, SEEK_END); length = fstream->_offset;
    fseek(fstream, 0, SEEK_SET);
    if (!((self->data = malloc(length)))) {
        fclose(fstream); LOG("failed memory allocation");
        return !((self->parent->parent->errored = true));
    }
    fread(self->data, length, 1, fstream); fclose(fstream);
    if (((self->data->magic = SWAP32(self->data->magic))) != MAGIC) {
        LOG("this file is not a champion");
        return !((self->parent->parent->errored = true));
    }
    self->data->size = SWAP32(self->data->size);
    return true;
}

uint8_t rom_read(ROMClass *self, uint16_t address)
{
    return *(self->context->memory + self->context->offset + address);
}

void rom_write(ROMClass *self, uint16_t address, uint8_t value)
{
    *(self->context->memory + self->context->offset + address) = value;
}
