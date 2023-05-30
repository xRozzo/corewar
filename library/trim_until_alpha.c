/*
** EPITECH PROJECT, 2023
** strlen.c
** File description:
** Get str length
*/

#include <string.h>

int isalpha_lowlevel(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

char* trim_until_alpha(char* input)
{
    if (input == NULL)
        return NULL;

    while (*input && !isalpha_lowlevel(*input))
        ++input;

    return input;
}
