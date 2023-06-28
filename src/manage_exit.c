/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** manage_exit
*/

#include "mysh.h"

int check_exit(int nb, int len, char *com, my_stats_t *my_stats)
{
    if (len > 2 || (nb == 0 && com[0] != '0')) {
        mini_printf("exit: Expression Syntax.\n", 2);
        my_stats->status = 2;
        return 1;
    }
    if (nb == -1) {
        my_stats->status = 2;
        mini_printf("exit: Badly formed number.\n", 2);
        return 1;
    }
    return 0;
}
