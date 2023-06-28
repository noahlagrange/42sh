/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** my_strcontacte
** my_strconcat
*/

#include "my.h"

char *my_strconcate(char *a, char *b)
{
    if (a == NULL)
        a = "";
    if (b == NULL)
        b = "";
    char *c = malloc(sizeof(char) * (my_strlen(a) + my_strlen(b) + 1));
    int i = 0;
    for ( ; a[i]; i++)
        c[i] = a[i];
    for (int j = 0; b[j]; j++, i++)
        c[i] = b[j];
    c[i] = 0;
    return c;
}
