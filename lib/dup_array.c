/*
** EPITECH PROJECT, 2023
** ast
** File description:
** dup_array
*/

#include "my.h"

char **dup_array(char **array)
{
    size_t len = len_array(array);
    char **new = NULL;

    if (len == 0)
        return NULL;
    new = malloc(sizeof(char *) * (len + 1));
    if (new == NULL)
        return NULL;
    int i = 0;
    for (; array[i]; i++) {
        new[i] = my_strdup(array[i]);
        if (new[i] == NULL)
            return NULL;
    }
    new[i] = NULL;
    return new;
}
