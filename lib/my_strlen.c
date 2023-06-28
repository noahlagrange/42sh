/*
** EPITECH PROJECT, 2022
** count char
** File description:
** oui
*/

#include "my.h"

int my_strlen(char const *str)
{
    int i;
    i = 0;

    if (str == NULL)
        return 0;
    while (str[i] != '\0')
        i++;
    return i;
}

int len_array(char **array)
{
    if (array == NULL)
        return 0;
    int i = 0;
    while (array[i] != NULL)
        i++;
    return i;
}

int my_strlento_bis(char *s, char *del)
{
    int i = 0;
    for (; s[i]; i++) {
        if (!skip(s[i], del))
            return i;
    }
    return i;
}
