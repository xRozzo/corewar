/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/corewar.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

char *plenish_coding_byte
(instructions_t *instr, char *hex_representation, int *i)
{
    for (; instr->args_type[*i]; (*i)++) {
        switch (instr->args_type[*i]) {
            case T_REG:
                my_strcat(hex_representation, "01");
                break;
            case T_LAB:
            case T_I:
            case T_DIR:
                my_strcat(hex_representation, "10");
                break;
            case T_IND:
                my_strcat(hex_representation, "11");
                break;
            default:
                my_strcat(hex_representation, "00");
                break;
        }
    }
    return hex_representation;
}

void write_parameter_to_output
(instructions_t *instr, FILE *output_file, int *instruction_size)
{
    int i = 0;
    char *hex_representation = malloc(sizeof(char) * 9);
    hex_representation = plenish_coding_byte(instr, hex_representation, &i);
    switch (instr->op) {
        case LIVE:
        case ZJMP:
        case FORK:
        case LFORK:
            *instruction_size -= 1; break;
        default:
            write_padding_to_output(&hex_representation, i);
            hex_representation[8] = '\0';
            uint8_t byte = binary_string_to_byte(hex_representation);
            fwrite(&byte, sizeof(byte), 1, output_file);
    }
}

void write_argument_to_output(parameters_t *params, parser_t *parser)
{
    switch (params->args_type) {
    case T_REG:
        write_register_to_output(params->arg, params->output_file);
        break;
    case T_DIR:
        write_direct_to_output(params->arg, params->output_file);
        break;
    case T_IND:
    case T_I:
        write_indirect_to_output(params->arg, params->output_file);
        break;
    case T_LAB:
        write_label_to_output(params, parser);
        break;
    default:
        break;
    }
}

void cnt_instruction_size(arg_type_t arg_type, int *instruction_size)
{
    switch (arg_type) {
    case T_REG:
        *instruction_size += REG_SIZE;
        break;
    case T_DIR:
        *instruction_size += DIR_SIZE;
        break;
    case T_I:
    case T_IND:
        *instruction_size += IND_SIZE;
        break;
    case T_LAB:
        *instruction_size += LAB_SIZE;
        break;
    default:
        break;
    }
}

void second_pass(parser_t *parser, FILE *fd)
{
    int offset = 0;
    parameters_t *params = malloc(sizeof(parameters_t));
    for (int i = 0; parser->instructions[i]; i++) {
        int instruction_size = 2;
        instructions_t *instr = parser->instructions[i];
        write_opcode_to_output(instr->op, fd);
        write_parameter_to_output(instr, fd, &instruction_size);
        for (int j = 0; instr->args[j]; j++) {
            cnt_instruction_size(instr->args_type[j], &instruction_size);
            *params = (typeof(*params)){.arg = instr->args[j],
                                        .current_offset = offset,
                                        .output_file = fd,
                                        .instr = instr,
                                        .args_type = instr->args_type[j],
                                        .instruction_size = instruction_size
            };
            write_argument_to_output(params, parser);
        }
        offset += instruction_size;
    }
}
