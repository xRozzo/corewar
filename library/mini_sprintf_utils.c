/*
** EPITECH PROJECT, 2023
** mini_sprintf.c
** File description:
** Mini mini_sprintf implementation
*/

#include "../include/common.h"

int copy_string(char *destination, const char *source)
{
    int count = 0;
    while (*source != '\0') {
        *(destination++) = *(source++);
        count++;
    }
    *destination = '\0';
    return count;
}

int int_to_string(char *buf, int num)
{
    int count = 0;
    if (num < 0) {
        *(buf++) = '-';
        num = -num;
        count++;
    }
    int divisor = 1;
    int temp = num;
    while (temp / 10 != 0) {
        divisor *= 10;
        temp /= 10;
    }
    while (divisor != 0) {
        int digit = num / divisor;
        *(buf++) = digit + '0';
        num %= divisor;
        divisor /= 10;
        count++;
    }
    return count;
}

int int_to_hex(char *buf, int num, int digits)
{
    int count = 0;
    int i;
    for (i = 0; i < digits; i++) {
        int digit = (num >> ((digits - 1 - i) * 4)) & 0xF;
        *(buf++) = digit < 10 ? digit + '0' : digit - 10 + 'A';
        count++;
    }
    return count;
}
