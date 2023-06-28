/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** color_panel2
*/

#include "../mysh.h"

int my_red(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = RED;
    if (status == 2)
        prompt->color_text = RED;
    return 0;
}

int my_cyan(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = CYAN;
    if (status == 2)
        prompt->color_text = CYAN;
    return 0;
}

int my_blue(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = BLUE;
    if (status == 2)
        prompt->color_text = BLUE;
    return 0;
}

int my_purple(prompt_t *prompt, int status)
{
    if (status == 1)
        prompt->color_prompt = PURPLE;
    if (status == 2)
        prompt->color_text = PURPLE;
    return 0;
}
