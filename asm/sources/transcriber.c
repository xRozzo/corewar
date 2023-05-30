/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"


void transcriber(parser_t *parser, FILE *fd, int prog_size)
{
    header_t *header = malloc(sizeof(header_t));
    header->magic = to_little_endian(MAGIC);
    my_strcpy(header->prog_name, parser->name);
    header->prog_size = to_little_endian(prog_size);
    my_strcpy(header->comment, parser->comment);
    fwrite(header, sizeof(header_t), 1, fd);
}
