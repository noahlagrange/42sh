/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** manage_str
*/

#include "my.h"

bool one_char_str(char *str)
{
    if (str == NULL)
        return false;
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            return false;
    return true;
}
