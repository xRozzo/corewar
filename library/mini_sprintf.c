/*
** EPITECH PROJECT, 2023
** mini_sprintf.c
** File description:
** Mini mini_sprintf implementation
*/

#include "../include/common.h"

int copy_string(char *, const char *);
int int_to_string(char *, int);
int int_to_hex(char *, int, int);

void handle_string(char **buf, va_list args, int *count)
{
    const char *str = va_arg(args, const char *);
    int len = copy_string(*buf, str);
    *buf += len;
    *count += len;
}

void handle_decimal(char **buf, va_list args, int *count)
{
    int num = va_arg(args, int);
    int len = int_to_string(*buf, num);
    *buf += len;
    *count += len;
}

void handle_hex(char **buf, va_list args, int *count, int width)
{
    int num = va_arg(args, int);
    int len = int_to_hex(*buf, num, width);
    *buf += len;
    *count += len;
}

void handle_format_strings(
    const char **fmt, char **buf, va_list *args, int *count)
{
    switch (*(++(*fmt))) {
        case 's': handle_string(buf, *args, count); break;
        case 'd': handle_decimal(buf, *args, count); break;
        case '-':
            if (*((*fmt) + 1) == '4' && *((*fmt) + 2) == 'X') {
                handle_hex(buf, *args, count, 4);
                (*fmt) += 2;
            }
            break;
        case '0':
            if (*((*fmt) + 1) == '2' && *((*fmt) + 2) == 'X') {
                handle_hex(buf, *args, count, 2);
                (*fmt) += 2;
            }
            break;
        default:
            *((*buf)++) = **fmt;
            (*count)++;
            break;
    }
}

int mini_sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int count = 0;

    while (*fmt != '\0') {
        if (*fmt == '%') {
            handle_format_strings(&fmt, &buf, &args, &count);
        } else {
            *(buf++) = *fmt;
            count++;
        }
        ++fmt;
    }
    *buf = '\0';
    va_end(args);

    return count;
}
