/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** check_history
*/

#include "../mysh.h"

int check_history_number(int nb, char *str)
{
    if (nb < 0) {
        mini_printf("Usage: history [-chrSLMT] [# number of events].\n", 2);
        return -1;
    }
    if (nb == 0 && str[0] != '0') {
        mini_printf("history: Badly formed number.\n", 2);
        return -1;
    }
    return nb;
}

int history_flags(my_stats_t *my_stats, char *flags)
{
    if (my_strcmp(flags, "-c") == 0) {
        destroy_history(my_stats->my_history->list->nodes);
        free(my_stats->my_history);
        my_stats->my_history = create_history();
    } else {
        printf("Invalid flag : -c\n");
        return -1;
    }
    return 0;
}
