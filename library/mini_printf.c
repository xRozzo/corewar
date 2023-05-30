/*
** EPITECH PROJECT, 2023
** mini_printf.c
** File description:
** Mini printf implementation
*/

#include "../include/common.h"

void mini_printf(const char *fmt, ...)
{
    va_list ap;
    const char *p;
    char *s;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            write(STDOUT_FILENO, p, 1);
            continue;
        }

        switch (*++p) {
            case 's':
                s = va_arg(ap, char *);
                write(STDOUT_FILENO, s, my_strlen(s));
                break;
            default: write(STDOUT_FILENO, p, 1); break;
        }
    }
    va_end(ap);
}
