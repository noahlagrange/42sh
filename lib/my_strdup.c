/*
** EPITECH PROJECT, 2022
** oui
** File description:
** oui
*/

#include "my.h"

char *my_strdup(char const *str)
{
    if (str == NULL)
        return NULL;
    int i = 0;
    i = my_strlen(str);
    char *str_cpy = malloc(sizeof(char) * (i + 1));
    if (str_cpy == NULL)
        exit(84);
    str_cpy = my_memset(str_cpy, 0, i);
    return my_strcpy(str_cpy, str);
}

void free_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++) {
        if (array[i] == NULL)
            continue;
        free(array[i]);
    }
    if (array == NULL)
        return;
    free(array);
}
