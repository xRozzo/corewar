/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** concatenates two strs
*/

#include <stddef.h>

char *my_strchr(char *str, int c)
{
    while (*str != '\0') {
        if (*str == (char)c)
            return str;
        str++;
    }
    if (*str == (char)c)
        return str;
    return NULL;
}
