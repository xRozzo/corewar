/*
** EPITECH PROJECT, 2023
** MY_H
** File description:
** my_str_to_array.c
*/

#include <stdlib.h>

int lines_counter(char *buff, char c1, char c2)
{
    int i = 0;
    int lines = 0;

    while (buff[i] != '\0') {
        if (buff[i] == c1 || buff[i] == c2)
            lines++;
        i++;
    }
    return (lines + 1);
}

int len_line(char *buff, int i, char c1, char c2)
{
    int len = 0;
    while (buff[i] != c1 && buff[i] != c2 && buff[i] != '\0') {
        i++;
        len++;
    }
    return (len);
}

char **my_str_to_array(char *buff, char c1, char c2)
{
    int lines = lines_counter(buff, c1, c2);
    char **array = malloc(sizeof(char *) * (lines + 1));
    int a = 0; int b; int i = 0;
    for (int j = 0; j <= lines; j++)
        array[j] = NULL;
    while (a < lines) {
        int len = len_line(buff, i, c1, c2);
        array[a] = malloc(sizeof(char) * (len + 1));
        b = 0;
        while (buff[i] != c1 && buff[i] != c2 && buff[i] != '\0') {
            array[a][b] = buff[i];
            b++;
            i++;
        }
        array[a][b] = '\0';
        if (buff[i]) i++;
        a++;
    }
    array[a] = NULL;
    return (array);
}
