/*
** EPITECH PROJECT, 2023
** get
** File description:
** man man
*/
#include "../mysh.h"

char *get_local_path(char *str)
{
    int i = 0;
    char *path = NULL;
    for (i = 0; str[i] != '\0' && str[i] != '/'; i++);
    path = slice_int(str, i);
    if (skip_tab(path, "*"))
        return strdup(".");
    return path;
}

char *get_pattern(char *str)
{
    int i = 0;
    char *pattern = NULL;
    if (!skip_tab(str, "/"))
        return str;
    for (i = 0; str[i] != '\0' && str[i] != '/'; i++);
    pattern = slice_int(str + i + 1, strlen(str) - i - 1);
    return pattern;
}
