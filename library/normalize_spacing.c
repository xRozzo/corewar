/*
** EPITECH PROJECT, 2023
** mini_sprintf.c
** File description:
** Mini mini_sprintf implementation
*/

#include "../include/common.h"

char *normalize_spacing(char *input)
{
    if (input == NULL)
        return NULL;

    char *label_end = my_strchr(input, ':');
    if (label_end == NULL || (label_end > input && *(label_end - 1) == '%'))
        return input;

    char* opcodeStart = label_end + 1;
    while (*opcodeStart && is_whitespace((unsigned char)*opcodeStart))
        ++opcodeStart;

    my_memmove(label_end + 2, opcodeStart, my_strlen(opcodeStart) + 1);
    label_end[1] = ' ';
    return input;
}
