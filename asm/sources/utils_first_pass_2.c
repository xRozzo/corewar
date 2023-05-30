/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

int which_opcode(char *word)
{
    char *opcodes[16] = {OPCODES01, OPCODES02};

    for (int i = 0; i < 16; i++)
        if (my_strcmp(word, opcodes[i]) == 0)
            return i + 1;
    return -1;
}

int line_counter(char *buff, char c)
{
    int i = 0;
    int lines = 0;
    while (buff[i] != '\0') {
        if (buff[i] == c)
            lines++;
        i++;
    }
    return (lines + 1);
}

char **my_str_to_array_whitespace(char *buff, char c)
{
    int lines = line_counter(buff, c);
    char **array = malloc(sizeof(char *) * (lines + 1));
    int a = 0; int i = 0;
    for (int j = 0; j <= lines; j++)
        array[j] = NULL;

    while (a != lines) {
        int start = i;
        while (buff[i] != c && buff[i] != '\0') {
            i++;
        }
        array[a] = malloc(sizeof(char) * (i - start + 1));
        my_strncpy(array[a], &buff[start], i - start);
        array[a][i - start] = '\0';
        i++;
        a++;
    }
    array[a] = NULL;
    return (array);
}

void handle_cases(parser_t *parser, indexes_t i, char **words, int arg_i)
{
    func_ptr cases[3][2] = {
            {handle_r_case, NULL},
            {handle_direct_case, handle_lab_case},
            {handle_ind_case, NULL}
    };
    int first_char_i = ((*words)[0] == 'r') ? 0 : ((*words)[0] == '%') ? 1 : 2;
    int second_char_i = ((*words)[0] == '%' && (*words)[1] == ':') ? 1 : 0;

    func_ptr chosen_case = cases[first_char_i][second_char_i];
    if (chosen_case != NULL)
        chosen_case(parser, i, arg_i);
}

void handle_comma(parser_t *parser, indexes_t indexes, int arg_i)
{
    if (parser->instructions[indexes.oc]->args[arg_i]
        [my_strlen(parser->instructions[indexes.oc]->args[arg_i]) - 1] == ',')
        parser->instructions[indexes.oc]->args[arg_i]
        [my_strlen(parser->instructions[indexes.oc]->args[arg_i]) - 1] = '\0';
}
