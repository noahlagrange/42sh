/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** append
*/

#include "my.h"

char **append(char **array, char *str)
{
    char **new = malloc(sizeof(char *) * (len_array(array) + 2));
    if (new == NULL)
        return NULL;
    int i = 0;
    for (; array[i] != NULL; i++)
        new[i] = array[i];
    new[i] = my_strdup(str);
    if (new[i] == NULL)
        return NULL;
    new[i + 1] = NULL;
    return new;
}
