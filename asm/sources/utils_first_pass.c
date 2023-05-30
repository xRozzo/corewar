/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** Main assembler entry point
*/

#include "../include/common.h"

int is_empty_or_whitespace(const char *str)
{
    if (str == NULL)
        return 1;
    while (*str) {
        if (!is_whitespace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

int is_empty_or_whitespace_or_header(const char *str)
{
    if (str == NULL)
        return 1;
    while (*str) {
        if (!is_whitespace((unsigned char)*str)) {
            return (*str == '.') ? 0 : 1;
        }
        str++;
    }
    return 1;
}

char *remove_comment(char *line)
{
    char *comment_start = my_strchr(line, '#');
    if (comment_start != NULL) {
        *comment_start = '\0';
    }
    return line;
}

char *merge_lines(char *line1, char *line2)
{
    char *merged_line = malloc(my_strlen(line1) + my_strlen(line2) + 2);
    mini_sprintf(merged_line, "%s %s", line1, line2);
    return merged_line;
}

int increment_j_on_invalid_line(char **lines, int j)
{
    while (lines[j] && (lines[j][0] == '#'
    || is_empty_or_whitespace(lines[j])))
        j++;
    return j;
}
