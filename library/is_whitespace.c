/*
** EPITECH PROJECT, 2023
** mini_printf.c
** File description:
** Mini printf implementation
*/

int is_whitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
    || c == '\r')
        return 1;
    return 0;
}
