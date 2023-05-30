/*
** EPITECH PROJECT, 2023
** STUMPER
** File description:
** read file
*/

#include "../include/common.h"

char *read_file(char *filepath, parser_t *parser)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL) exit(84);
    size_t len = 0;
    char *line = NULL;
    char *buff = malloc(1);
    buff[0] = '\0';
    while (getline(&line, &len, file) != -1) {
        size_t new_len = my_strlen(buff) + len + 1;
        char *new_buff = malloc(new_len);
        new_buff[0] = '\0';
        my_strcat(new_buff, buff);
        my_strcat(new_buff, line);
        free(buff);
        buff = new_buff;
    }
    free(line);
    filepath[my_strlen(filepath) - 2] = '\0';
    parser->file_name = filepath;
    fclose(file);
    return buff;
}
