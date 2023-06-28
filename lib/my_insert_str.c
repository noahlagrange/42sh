/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** my_insert_str
*/

#include "my.h"

char *insert_str(char *str, char *add, int n)
{
    int len = 0;
    if (str != NULL)
        len = strlen(str);
    char *new = malloc(sizeof(char) * (len + strlen(add) + 1));
    int i = 0;
    int i_cpy = 0;
    for (; str != NULL && i < n && str[i] != '\0'; i++)
        new[i] = str[i];
    i_cpy = i;
    for (int j = 0; add[j] != '\0'; j++, i++)
        new[i] = add[j];
    for (; str != NULL && str[i_cpy] != '\0'; i++, i_cpy++)
        new[i] = str[i_cpy];
    new[i] = '\0';
    return new;
}

char *insert_char(char *str, char add, int n)
{
    int len = 0;
    if (str != NULL)
        len = strlen(str);
    char *new = malloc(sizeof(char) * (len + 2));
    int i = 0;

    for (; i < n && str[i] != '\0'; i++)
        new[i] = str[i];
    new[i] = add;
    new[i + 1] = '\0';
    return new;
}
