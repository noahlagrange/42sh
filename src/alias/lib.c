/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** lib
*/
#include "../mysh.h"

size_t my_all_arraylen(char **arr)
{
    size_t len = 0;
    if (arr == NULL)
        return 0;
    for (size_t i = 0; arr[i]; i++)
        len += strlen(arr[i]);
    return len;
}

char *get_first_word(char *s, char delim)
{
    char *new = malloc(sizeof(char) * (strlen(s) + 1));
    int i = 0;
    for (i = 0; s[i] && s[i] != delim; i++)
        new[i] = s[i];
    new[i] = '\0';
    return new;
}

char *replace_char(char *s, char old, char new)
{
    for (int i = 0; s && s[i]; i++) {
        if (s[i] == old)
            s[i] = new;
    }
    return s;
}

char *array_to_str(char **arr)
{
    int len = my_all_arraylen(arr) + len_array(arr);
    char *new = (len > 0) ? malloc(sizeof(char) * len + 1) : NULL;
    if (new == NULL)
        return NULL;
    int ind = 0;
    for (int i = 0; arr[i]; i++) {
        for (int j = 0; arr[i][j]; j++)
            new[ind++] = arr[i][j];
        new[ind++] = ' ';
    }
    new[ind] = '\0';
    return new;
}

void pop_array(char **arr, int i)
{
    if (i >= len_array(arr) || arr[i] == NULL)
        return;
    MY_FREE(arr[i], free);
    for (; arr[i + 1]; i++)
        arr[i] = arr[i + 1];
}
