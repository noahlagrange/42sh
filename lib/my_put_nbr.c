/*
** EPITECH PROJECT, 2022
** EPITECH PROJECT
** File description:
** day2
*/

#include "my.h"

int my_put_nbr(int nb)
{
    int i = 0;
    int p = 1;

    if (nb < 0) {
        nb = -nb;
        i = i + my_putchar('-', 1);
    }
    while (nb / p >= 9) {
        p = p * 10;
    }
    while (p >= 1) {
        i = i + my_putchar((nb / p) % 10 + '0', 1);
        p = p / 10;
    }
    return i;
}

int my_printdigits(va_list *list, int fd)
{
    (void)fd;
    return my_put_nbr(va_arg(*list, int));
}
