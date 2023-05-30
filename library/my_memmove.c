/*
** EPITECH PROJECT, 2023
** mini_sprintf.c
** File description:
** Mini mini_sprintf implementation
*/

#include <stdlib.h>

void *my_memmove(void *dest, const void *src, size_t n)
{
    char* destChar = (char*)dest;
    const char* srcChar = (const char*)src;

    char* temp = (char*)malloc(n);
    if (temp == NULL)
        return NULL;

    for (size_t i = 0; i < n; ++i)
        temp[i] = srcChar[i];

    for (size_t i = 0; i < n; ++i)
        destChar[i] = temp[i];
    free(temp);
    return dest;
}
