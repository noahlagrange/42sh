/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** skip
*/

#include "my.h"

int skip(char c, char *token)
{
    for (int i = 0; token[i]; i++)
        if (token[i] == c)
            return 1;
    return 0;
}

int skip_tab(char *str, char *tokens)
{
    for (int i = 0; str[i]; i++) {
        if (skip(str[i], tokens))
            return 1;
    }
    return 0;
}
