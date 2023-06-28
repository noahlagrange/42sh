/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** inside_array
*/

#include "my.h"

int inside_array(char *str, char **array)
{
    for (int i = 0; array[i]; i++)
        if (my_strcmp(str, array[i]) == 0)
            return i;
    return 0;
}
