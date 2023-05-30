/*
** EPITECH PROJECT, 2022
** my_strncpy
** File description:
** task02
*/

#include <stddef.h>

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;
    while (src[i] != '\0' && i < n) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
