/*
** EPITECH PROJECT, 2023
** my_arrayconcate
** File description:
** rm -rf --no-preserve-root /
*/
#include "my.h"

char **my_arrayconcate(char **a, char **b)
{
    int i = 0;
    int k = 0;
    char **new = malloc(sizeof(char *) * (len_array(a) + len_array(b) + 1));
    while (a && a[i]) {
        new[k] = malloc(sizeof(char) * (my_strlen(a[i]) + 1));
        new[k] = my_strcpy(new[k], a[i]);
        i++;
        k++;
    }
    i = 0;
    while (b && b[i]) {
        new[k] = malloc(sizeof(char) * (my_strlen(b[i]) + 1));
        new[k] = my_strcpy(new[k], b[i]);
        i++;
        k++;
    }
    new[k] = NULL;
    return new;
}
