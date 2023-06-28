/*
** EPITECH PROJECT, 2022
** oui
** File description:
** oui
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int i = 0;
    int len_dest = my_strlen(dest);

    if (src == NULL)
        return dest;
    while (src[i] != '\0') {
        dest[len_dest + i] = src[i];
        i++;
    }
    dest[len_dest + i] = '\0';
    return dest;
}

int skip_array(char *c, char **token)
{
    int i = 0;
    int len = my_strlen(c);
    for (; token[i]; i++) {
        if (my_strncmp(c, token[i], len) == 0 &&
        token[i][len] == '=')
            return i;
    }
    return -1;
}

char **free_path(char **gree)
{
    for (int i = 1; gree[i]; i++)
        free(gree[i]);
    gree[1] = NULL;
    return gree;
}

void *my_memset(void *s, size_t j, size_t size)
{
    for (size_t i = 0; size > i; i++)
        ((char*)s)[i] = j;
    return s;
}

int array_skip(char *c, char **tab)
{
    for (int i = 1; tab[i]; i++) {
        int size_tab = my_strlen(tab[i]);
        if (my_strncmp(c, tab[i], size_tab) == 0 && ((c + size_tab)[0] == '='))
            return 1;
    }
    return -1;
}
