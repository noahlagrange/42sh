/*
** EPITECH PROJECT, 2023
** prompt
** File description:
** prompt
*/

#include "../mysh.h"

void default_prompt(my_stats_t *my_stats)
{
    char *prompt = NULL;
    prompt = getcwd(NULL, 0);
    if (isatty(0) == 1) {
        if (my_stats->prompt->color_prompt != NULL)
            printf("%s", my_stats->prompt->color_prompt);
        printf("[%s]$ ", prompt);
        if (my_stats->prompt->color_text != NULL)
            printf("%s", my_stats->prompt->color_text);
    }
    MY_FREE(prompt, free);
}

int prompt(my_stats_t *my_stats)
{
    int index = 1;
    if (index == 1) {
        default_prompt(my_stats);
    }
    return 0;
}
