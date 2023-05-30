/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

arg_type_t index_or_direct(opcode_t opcode, int *lc)
{
    if (opcode == ZJMP || opcode == LDI || opcode == STI ||
        opcode == LLDI || opcode == FORK || opcode == LFORK) {
            *lc += 2;
            return T_I;
        }
    *lc += 4;
    return T_DIR;
}

void handle_r_case(parser_t *parser, indexes_t i, int arg_i)
{
    parser->instructions[i.oc]->args_type[arg_i] = T_REG;
    *i.lc += 1;
}

void handle_lab_case(parser_t *parser, indexes_t i, int arg_i)
{
    parser->instructions[i.oc]->args_type[arg_i] = T_LAB;
    *i.lc += 2;

    switch (parser->instructions[i.oc]->op) {
        case FORK:
        case LFORK:
            *i.lc += 2;
            break;
        default:
            break;
    }

}

void handle_direct_case(parser_t *parser, indexes_t i, int arg_i)
{
    parser->instructions[i.oc]->args_type[arg_i] =
            index_or_direct(parser->instructions[i.oc]->op, i.lc);
}

void handle_ind_case(parser_t *parser, indexes_t i, int arg_i)
{
    parser->instructions[i.oc]->args_type[arg_i] = T_IND;
    *i.lc += 2;
}
