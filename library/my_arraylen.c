/*
** EPITECH PROJECT, 2023
** mini_sprintf.c
** File description:
** Mini mini_sprintf implementation
*/

int my_arraylen(char **array)
{
    int i = 0;
    for (; array[i]; i++);
    return i;
}
