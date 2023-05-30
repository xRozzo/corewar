/*
** EPITECH PROJECT, 2023
** strlen.c
** File description:
** Get str length
*/

int my_strlen(char const *str)
{
    char const *start = str;
    while (*str != '\0')
        str++;
    return str - start;
}
