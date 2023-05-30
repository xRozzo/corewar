/*
** EPITECH PROJECT, 2023
** common.h
** File description:
** Project constants
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef __COMMON
    #define __COMMON

    #define UNUSED __attribute__((unused))

    #define MAX_MEMORY    0x1800
    #define MAX_REGISTERS 0x10
    #define MAGIC         0xEA83f3
    #define MAX_CYCLES    0x600
    #define CYCLE_STEP    0x5
    #define NBR_LIVE      0x28
    #define NAME_LEN      0x80
    #define COMM_LEN      0x800
    #define IDX_MOD       0x200
    #define MAX_WARRIORS  0x200

    #define ZJMP_ARGS 0x03
    #define STI_ARGS  0x03
    #define LDI_ARGS  0x03
    #define ST_ARGS   0x02
    #define LD_ARGS   0x02

    #define COMMENT         '#'
    #define LABEL           ':'
    #define DIRECT          '%'
    #define SEPARATOR       ','
    #define COMMAND_SECTION ".name"
    #define COMMENT_SECTION ".comment"

    #define COLOR_RED     "\x1b[31m"
    #define COLOR_GREEN   "\x1b[32m"
    #define COLOR_YELLOW  "\x1b[33m"
    #define COLOR_MAGENTA "\x1b[35m"
    #define COLOR_RESET   "\x1b[0m"

    #define OPCODES01 "live", "ld", "st", "add", "sub", "and", "or", "xor"
    #define OPCODES02 \
        "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"

    #define SWAP16(n) __builtin_bswap16(n)
    #define SWAP32(n) __builtin_bswap32(n)

    #define HANDLE_ERROR(e)     \
        do {                    \
            exit(EXIT_FAILURE); \
        } while (0)
    #define LOG(m) \
        mini_printf("info :: %s:%s() - %s\n", __FILE__, __func__, m);
    #define NOT_IMPLEMENTED() \
        mini_printf(          \
            "warn :: %s:%s() - %s\n", __FILE__, __func__, "Not implemented");
    #define FAST_PRINT(fmt, ...)                                \
        ({                                                      \
            char buff[128];                                     \
            int64_t len = mini_sprintf(buff, fmt, __VA_ARGS__); \
            write(STDOUT_FILENO, buff, len);                    \
        });

typedef struct {
    char *path;
    bool running;
    uint8_t uuid;
    int64_t cycle;
    int64_t alive_cycle;
    int64_t next_cycle;
} warrior_context_t;

typedef struct {
    int32_t magic;
    char name[NAME_LEN];
    uint8_t _null_name;
    int32_t size;
    char comm[COMM_LEN];
    int32_t _null_comm;
    uint8_t data[];
} rom_data_t;

typedef struct {
    int32_t r1;
    int32_t r2;
    int32_t r3;
    int32_t r4;
    int32_t r5;
    int32_t r6;
    int32_t r7;
    int32_t r8;
    int32_t r9;
    int32_t r10;
    int32_t r11;
    int32_t r12;
    int32_t r13;
    int32_t r14;
    int32_t r15;
    int32_t r16;
    uint16_t pc;
    uint8_t c : 1;
} registers_t;

typedef enum {
    RT_NONE,
    RT_1,
    RT_2,
    RT_3,
    RT_4,
    RT_5,
    RT_6,
    RT_7,
    RT_8,
    RT_9,
    RT_10,
    RT_11,
    RT_12,
    RT_13,
    RT_14,
    RT_15,
    RT_16,
    RT_PC,
    RT_C,
    _RT_COUNT,
} register_type_t;

typedef enum {
    IN_NONE,
    IN_LIVE,
    IN_LD,
    IN_ST,
    IN_ADD,
    IN_SUB,
    IN_AND,
    IN_OR,
    IN_XOR,
    IN_ZJMP,
    IN_LDI,
    IN_STI,
    IN_FORK,
    IN_LLD,
    IN_LLDI,
    IN_LFORK,
    IN_AFF,
    _IN_COUNT,
} instruction_type_t;

typedef enum {
    CT_NONE,
    CT_NC,
    CT_C,
} condition_type_t;

typedef enum {
    CB_NONE,
    CB_REGISTER,
    CB_DIRECT,
    CB_INDIRECT,
} coding_byte_t;

typedef union {
    struct {
        uint8_t param_4 : 2;
        uint8_t param_3 : 2;
        uint8_t param_2 : 2;
        uint8_t param_1 : 2;
    };
    uint8_t raw;
} byte_aux_t;

typedef struct {
    instruction_type_t type;
    byte_aux_t byte;
    condition_type_t condition;
    bool is_relative;
    int32_t cycles;
} instruction_t;

typedef struct {
    int32_t param_1;
    coding_byte_t byte_1;
    int32_t param_2;
    coding_byte_t byte_2;
    int32_t param_3;
    coding_byte_t byte_3;
} fetched_data_t;

typedef struct {
    registers_t registers;
    fetched_data_t fetched_data;
    uint8_t op_code;
    instruction_t *instr;
} cpu_context_t;

typedef struct cpu_aux CPUClass;

typedef void (*proc_fn)(CPUClass *);

typedef struct {
    char *path;
    uint8_t *memory;
    uint64_t offset;
} rom_context_t;

typedef enum {
    LIVE = 0x01,
    LD = 0x02,
    ST = 0x03,
    ADD = 0x04,
    SUB = 0x05,
    AND = 0x06,
    OR = 0x07,
    XOR = 0x08,
    ZJMP = 0x09,
    LDI = 0x0a,
    STI = 0x0b,
    FORK = 0x0c,
    LLD = 0x0d,
    LLDI = 0x0e,
    LFORK = 0x0f,
    AFF = 0x10
} opcode_t;

typedef enum {
    T_REG = 1,
    T_DIR = 2,
    T_I = 3,
    T_IND = 4,
    T_LAB = 5
} arg_type_t;

typedef enum arg_size_s {
    REG_SIZE = 1,
    DIR_SIZE = 4,
    IND_SIZE = 2,
    LAB_SIZE = 2
} arg_size_t;

typedef struct header_s {
    int magic;
    char prog_name[NAME_LEN + 1];
    int prog_size;
    char comment[COMM_LEN + 1];
} header_t;

typedef struct instruction_s {
    opcode_t op;
    char *label;
    char **args;
    arg_type_t *args_type;
    int8_t label_offset;
} instructions_t;

typedef struct parser_s {
    char *file_name;
    char *name;
    char *comment;
    instructions_t **instructions;
} parser_t;

typedef struct indexes_s {
    int oc;
    int *lc;
} indexes_t;

typedef struct parameters {
    char *arg;
    int current_offset;
    FILE *output_file;
    instructions_t *instr;
    arg_type_t args_type;
    int instruction_size;
} parameters_t;

typedef void (*func_ptr)(parser_t *, indexes_t, int);

typedef void (*func_ptr)(parser_t *, indexes_t, int);

uint8_t binary_string_to_byte(const char *binary_string);
void write_padding_to_output(char **hex_representation, int i);
void get_name_and_comment(char **lines, parser_t *parser);
int handle_labeled_instruction(char **words, parser_t *parser, int oc, int lc);
int to_little_endian(int value);
char *normalize_spacing(char *input);
void *my_memmove(void *dest, const void *src, size_t n);
char *trim_until_alpha(char *input);
char **my_str_to_array_2(char *buff, char c, char c2);
int my_arraylen(char **array);
void handle_comma(parser_t *parser, indexes_t indexes, int arg_i);
int is_empty_or_whitespace(const char *);
char *merge_lines(char *, char *);
int increment_j_on_invalid_line(char **, int);
char *remove_comment(char *);
void handle_cases(parser_t *, indexes_t, char **, int);
char **my_str_to_array_whitespace(char *, char);
int line_counter(char *, char);
int which_opcode(char *);
arg_type_t index_or_direct(opcode_t, int *);
void handle_r_case(parser_t *, indexes_t, int);
void handle_lab_case(parser_t *, indexes_t, int);
void handle_direct_case(parser_t *, indexes_t, int);
void handle_ind_case(parser_t *, indexes_t, int);
int is_empty_or_whitespace_or_header(const char *);
void free_lines(char **);
void transcriber(parser_t *, FILE *, int);
char *my_strcpy(char *, char const *);
int is_whitespace(char);
void *my_memcpy(void *, const void *, int32_t);
void *my_memset(void *, int32_t, int64_t);
int my_strcmp(char const *, char const *);
int my_strlen(char const *);
char *remove_character(char *, char);
char *my_strncpy(char *, char const *, int);
char **my_str_to_array(char *, char);
void mini_printf(const char *, ...);
char *read_file(char *, parser_t *);
int parser(char *, parser_t *);
char *my_strcat(char *, char const *);
char *my_strdup(char const *);
int mini_sprintf(char *, const char *, ...);
char *my_strchr(char *, int);
char *remove_spaces(char *);
void second_pass(parser_t *, FILE *);
void write_opcode_to_output(opcode_t, FILE *);
void write_register_to_output(char *, FILE *);
void write_direct_to_output(char *, FILE *);
void write_indirect_to_output(char *, FILE *);
void write_label_to_output(parameters_t *, parser_t *);
int16_t to_little_endian_short(int16_t);
int get_direct_or_indirect_number(char *);
char *get_label_name(char *);
int get_register_number(char *);
int my_atoi(const char *);
#endif
