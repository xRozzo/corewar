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

int get_register_number(char *arg)
{
    return (arg[1] - '0');
}

int get_direct_or_indirect_number(char *arg)
{
    int i = 1;
    int nb = 0;
    if (arg[1] == '1' && arg[2] == '\0')
        return 1;
    for (; arg[i]; i++) {
        nb *= 10;
        nb = nb + arg[i] - '0';
    }
    return nb;
}

char *get_label_name(char *arg)
{
    int i = 2;
    char *label_name = malloc(sizeof(char) * my_strlen(arg));
    for (; arg[i]; i++) {
        label_name[i - 2] = arg[i];
    }
    label_name[i - 2] = '\0';
    return label_name;
}
