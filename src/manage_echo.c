/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** manage_echo
*/

#include "mysh.h"

char *add_in_echo(char *str, char *command, int n, char **env)
{
    int index = 0;
    char *tmp = slice(command, "$");
    if (tmp[0] == '$') {
        tmp = slice(command + 1, " ");
        if ((index = skip_array(tmp, env)) == -1) {
            mini_printf("%s: Undefined variable.\n", 2, tmp);
            return NULL;
        }
        str = insert_str(str, env[index] + strlen(tmp) + 1, n);
    } else {
        str = insert_str(str, tmp, n);
    }
    return str;
}

char *check_echo(char **tab, my_stats_t *my_stats)
{
    char *str = NULL;
    int n = 0;
    char *save = NULL;
    int i = 1;
    for (i = 1; tab[i] && tab[i + 1]; i++) {
        str = add_in_echo(str, tab[i], n, my_stats->my_env);
        n += my_strlen(str);
        if (str == NULL)
            return NULL;
        save = str;
        str = insert_char(str, ' ', n);
        free(save);
        n++;
    }
    return add_in_echo(str, tab[i], n, my_stats->my_env);
}

int my_echo(char **tab, my_stats_t *my_stats)
{
    char *str = NULL;
    if (len_array(tab) == 1) {
        mini_printf("\n", 1);
        return 0;
    }
    if (strcmp(tab[1], "$?") == 0)
        return 0 * printf("%d\n", my_stats->status);
    if ((str = check_echo(tab, my_stats)) == NULL) {
        my_stats->status = 84;
        return 84;
    }
    mini_printf("%s", 1, str);
    mini_printf("\n", 1);
    return 0;
}
