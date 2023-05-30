/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"
#include <stdio.h>

char **assemble_to_array(char *buff)
{
    char **lines = my_str_to_array_whitespace(buff, '\n');
    int total_lines = 0;
    while (lines[total_lines]) total_lines++;
    char **out_array = malloc(sizeof(char *) * (total_lines + 1));
    int out_idx = 0;
    for (int i = 0; i < total_lines; i++) {
        if (lines[i][0] == '#' || is_empty_or_whitespace(lines[i])) continue;
        lines[i] = remove_comment(lines[i]);
        if (lines[i][my_strlen(lines[i]) - 1] == ':') {
            int j = i + 1;
            increment_j_on_invalid_line(lines, j);
            out_array[out_idx++] = (lines[j]) ?
                    merge_lines(lines[i], lines[j]) : my_strdup(lines[i]);
            i = (lines[j]) ? j : i;
        } else
            out_array[out_idx++] = my_strdup(lines[i]);
    }
    out_array[out_idx] = NULL;
    free_lines(lines);
    return out_array;
}

void handle_coding_byte(parser_t *parser, int *lc)
{
    for (int i = 0; parser->instructions[i]; i++) {
        switch (parser->instructions[i]->op) {
            case ZJMP:
            case FORK:
            case LFORK:
                *(lc) -= 1;
                break;
            default:
                break;
        }
    }
}

void store_args(parser_t *parser, char **words, int oc, int *lc)
{
    int arg_i = 0;
    indexes_t indexes = {oc, lc};
    parser->instructions[oc]->args = malloc(sizeof(char *) * 4);
    parser->instructions[oc]->args_type = malloc(sizeof(arg_type_t) * 4);
    while (words && *words) {
        handle_cases(parser, indexes, words, arg_i);
        parser->instructions[indexes.oc]->args[arg_i] = my_strdup(*words);
        handle_comma(parser, indexes, arg_i);
        arg_i++;
        words++;
    }
    handle_coding_byte(parser, lc);
}

int get_instructions(parser_t *parser, char **lines)
{
    int oc = 0;
    int lc = 0;
    int mnemonic;
    parser->instructions = malloc(sizeof(instructions_t *) * 100);
    for (int i = 0; lines[i]; i++) {
        if (!is_empty_or_whitespace_or_header(lines[i])) continue;
        lines[i] = trim_until_alpha(lines[i]);
        lines[i] = normalize_spacing(lines[i]);
        parser->instructions[oc] = malloc(sizeof(instructions_t));
        char **words = my_str_to_array_2(lines[i], ' ', '\t');
        for (int j = 0; words[j]; j++) remove_spaces(words[j]);
        int j = handle_labeled_instruction(words, parser, oc, lc);
        if ((mnemonic = which_opcode(words[j++])) != - 1)
            parser->instructions[oc]->op = mnemonic;
        store_args(parser, words + j, oc, &lc);
        lc += 2, oc++;
    }
    return lc;
}

int parser(char *file, parser_t *parse)
{
    char **lines = assemble_to_array(file);
    get_name_and_comment(lines, parse);
    return get_instructions(parse, lines);
}
