/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

#ifndef __COREWAR_TEST
int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    parser_t *parse = malloc(sizeof(parser_t));
    char *assembly_file = read_file(argv[1], parse);
    char **directory_array = my_str_to_array(argv[1], '/');
    char *file_name = directory_array[my_arraylen(directory_array) - 1];
    FILE *fd = fopen(my_strcat(file_name, ".cor"), "w+");
    int prog_size = parser(assembly_file, parse);
    transcriber(parse, fd, prog_size);
    second_pass(parse, fd);
    return 0;
}
#endif
