/*
** EPITECH PROJECT, 2023
** corewar.c
** File description:
** Test corewar methods
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

int test(void);

Test(test, does_something)
{
    cr_assert_eq(test(), 0);
}
