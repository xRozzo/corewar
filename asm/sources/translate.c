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

void write_opcode_to_output(opcode_t opcode, FILE *output_file)
{
    uint8_t byte = opcode;
    fwrite(&byte, sizeof(byte), 1, output_file);
}

void write_register_to_output(char *arg, FILE *output_file)
{
    int byte = get_register_number(arg);
    uint8_t byte_as_uint8 = (uint8_t)byte;
    fwrite(&byte_as_uint8, sizeof(byte_as_uint8), 1, output_file);
}

void write_direct_to_output(char *arg, FILE *output_file)
{
    int byte = get_direct_or_indirect_number(arg);
    int little_endian_byte = to_little_endian(byte);
    uint32_t byte_as_uint32 = (uint32_t)little_endian_byte;
    fwrite(&byte_as_uint32, sizeof(byte_as_uint32), 1, output_file);
}

void write_indirect_to_output(char *arg, FILE *output_file)
{
    int byte = get_direct_or_indirect_number(arg);
    uint16_t byte_as_uint16 = (uint16_t)byte;
    uint16_t little_endian_byte = to_little_endian_short(byte_as_uint16);
    fwrite(&little_endian_byte, sizeof(little_endian_byte), 1, output_file);
}

void write_label_to_output(parameters_t *params, parser_t *parser)
{
    int label_offset = 0;
    char *label_name = get_label_name(params->arg);
    for (int i = 0; parser->instructions[i]; i++) {
        if (parser->instructions[i]->label) {
            (my_strcmp(parser->instructions[i]->label, label_name) == 0)
                ? label_offset = parser->instructions[i]->label_offset
                : 0;
        }
    }
    uint16_t label_address = label_offset;
    uint16_t relative_label_address = label_address - params->current_offset;
    uint16_t little_endian_byte =
        to_little_endian_short(relative_label_address);
    fwrite(&little_endian_byte, sizeof(little_endian_byte), 1,
    params->output_file);
}
