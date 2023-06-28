/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** all_color
*/

#include "../mysh.h"

int my_black(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = BLACK;
    if (status == 2)
        prompt->color_text = BLACK;
    return 0;
}

int my_yellow(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = YELLOW;
    if (status == 2)
        prompt->color_text = YELLOW;
    return 0;
}

int my_green(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = GREEN;
    if (status == 2)
        prompt->color_text = GREEN;
    return 0;
}
