/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

void get_name_and_comment(char **lines, parser_t *parser)
{
    char **words = my_str_to_array(lines[0], '"');
    parser->name = words[1];
    words = my_str_to_array(lines[1], '"');
    parser->comment = words[1];
}

int handle_labeled_instruction(char **words, parser_t *parser, int oc, int lc)
{
    int j = 0;
    if (words[j][my_strlen(words[j]) - 1] == ':') {
        parser->instructions[oc]->label_offset = lc;
        words[j][my_strlen(words[j]) - 1] = '\0';
        parser->instructions[oc]->label = words[j];
        j++;
    }
    return j;
}
