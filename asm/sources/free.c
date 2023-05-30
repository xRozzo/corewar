/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

void free_lines(char **lines)
{
    for (int i = 0; lines[i]; i++) free(lines[i]);
    free(lines);
}
