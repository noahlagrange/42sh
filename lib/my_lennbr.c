/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** my_lennbr
*/

int my_lennbr(long long nb)
{
    int i = 0;
    long long d = 1;

    if (nb < 0) {
        nb = -nb;
        i++;
    }
    if (nb == 0)
        return 1;
    while (nb / d > 0) {
        d = d * 10;
        i++;
    }
    return i;
}
