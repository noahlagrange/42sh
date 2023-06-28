/*
** EPITECH PROJECT, 2023
** src/my_builtins
** File description:
** try not to segfault, good luck :)
*/
#include "mysh.h"

bool my_isdigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool is_number(char *s)
{
    for (int i = 0; s[i]; i++)
        if (!my_isdigit(s[i]))
            return false;
    return true;
}

int my_repeat(char **command, my_stats_t *my_stats)
{
    int n = 0;
    if (!is_number(command[1])) {
        dprintf(2, "repeat: Badly formed number.\n");
        return 1;
    } else {
        n = atoi(command[1]);
        for (int i = 0; i < n; i++)
            parser_line(my_stats, array_to_str(command + 2));
    }
    return (my_stats->status == 84) ? 1 : 0;
}
