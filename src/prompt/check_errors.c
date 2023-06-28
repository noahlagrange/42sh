/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** check_errors
*/

#include "../mysh.h"

int check_input_color(char *color[], char *flags)
{
    int passed = 0;
    for (int i = 0;color[i] != 0;i++) {
        if (my_strcmp(flags, color[i]) == 0) {
            return passed;
        }
    }
    passed = 1;
    return passed;
}

int check_input_flag(char *flags)
{
    int passed = 0;
    if (my_strcmp(flags, "--full") == 0) {
        return passed;
    }
    passed = 1;
    return passed;
}

int check_args_valid(char **tab)
{
    int return_error = 0;
    if (check_input_flag(tab[1]) == 1) {
        printf("Invalid Flag : --full\n");
        return_error = 1;
    }
    if (check_color_valid(tab[2]) == 1)
        return_error = 1;
    return return_error;
}

int change_promt_color(char **tab, my_stats_t *my_stats, color_t COLOR[])
{
    my_stats->prompt->status = 1;
    change_color(tab[1], COLOR, my_stats->prompt);
    return 0;
}

int change_text_color(char **tab, my_stats_t *my_stats, color_t COLOR[])
{
    my_stats->prompt->status = 2;
    change_color(tab[2], COLOR, my_stats->prompt);
    return 0;
}
