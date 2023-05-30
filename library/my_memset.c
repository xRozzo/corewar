/*
** EPITECH PROJECT, 2023
** my_memcpy
** File description:
** Copy memory
*/

#include <stdint.h>

void *my_memset(void *pointer, int32_t ch, uint64_t length)
{
    uint8_t *ptr = pointer;
    for (int i = length; i > 0; i--)
        *ptr++ = (uint8_t) ch;
    return pointer;
}
