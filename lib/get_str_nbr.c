/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** get_str_nbr
*/

#include "my.h"

int my_deci(int a)
{
    if (a < 0)
        a = a * -1;
    int b = 1;
    while (a > 9) {
        a = a / 10;
        b = b * 10;
    }
    return (b);
}

int nb_line(int nb)
{
    int i = 1;
    while (nb != 0) {
        nb = nb / 10;
        i += i;
    }
    return i;
}

char *get_str_nbr(int nb)
{
    int deci = my_deci(nb);
    char *str = malloc(sizeof(char) * nb_line(nb) + 1);
    int modulo = 0;
    int i = 0;
    if (nb < 0) {
        str[i] = '-';
        nb = nb * -1;
        i++;
    }
    while (deci > 0) {
        modulo = nb % deci;
        nb = nb / deci;
        str[i] = nb + 48;
        nb = modulo;
        deci = deci / 10;
        i += 1;
    }
    str[i] = '\0';
    return (str);
}
