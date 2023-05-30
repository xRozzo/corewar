/*
** EPITECH PROJECT, 2022
** my_strcat.c
** File description:
** concatenates two strs
*/

#include "../include/common.h"

char *my_strcat(char *dest, char const *src)
{
    int index = 0;
    int dest_len = my_strlen(dest);

    if (src == NULL || dest == NULL)
        return NULL;
    while (src[index] != '\0') {
        dest[index + dest_len] = src[index];
        index++;
    }
    dest[index + dest_len] = '\0';
    return dest;
}
