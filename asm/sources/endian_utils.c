/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

int to_little_endian(int value)
{
    int result = 0;
    result |= (value & 0xFF000000) >> 24;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x000000FF) << 24;
    return result;
}

int16_t to_little_endian_short(int16_t value)
{
    int16_t result = 0;
    result |= (value & 0xFF00) >> 8;
    result |= (value & 0x00FF) << 8;
    return result;
}
