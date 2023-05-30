/*
** EPITECH PROJECT, 2022
** my_strcpy.c
** File description:
** Copy str 1 into str 2
*/

#include <stddef.h>

char *my_strcpy(char *dest, char const *src)
{
    int index = 0;

    if (src == NULL || dest == NULL)
        return NULL;
    while (src[index] != '\0') {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}
