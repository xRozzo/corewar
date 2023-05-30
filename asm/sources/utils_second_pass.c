/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/corewar.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t binary_string_to_byte(const char *binary_string)
{
    uint8_t byte = 0;
    while (*binary_string) {
        byte <<= 1;
        if (*binary_string++ == '1')
            byte |= 1;
    }
    return byte;
}

void write_padding_to_output(char **hex_representation, int i)
{
    for (; i < 4; i++)
        my_strcat(*hex_representation, "00");
}
