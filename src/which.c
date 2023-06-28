/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** which
*/

#include "mysh.h"

int check_access_path_which(char *path_command)
{
    int count = 0;
    if (access(path_command, X_OK) == 0) {
        printf("%s\n", path_command);
        count++;
    } else {
        count = -1;
    }
    return count;
}

void find_break(char *command, char **path)
{
    int stock = 0;
    for (int i = 1;path[i] != NULL;i++) {
        if (check_end_str(path[i], '/') == 0) {
            strcat(strcat(path[i], "/"), command);
            stock = check_access_path_which(path[i]);
        }
        if (stock == 1)
            break;
    }
}

int check_alias_which(char *command, my_stats_t *states)
{
    alias_t *tmp = NULL;
    LIST_FOREACH_DECL_BASIC(states->alias->nodes, elem) {
        tmp = CAST(alias_t *, elem->data);
        if (my_strcmp(command, tmp->alias) == 0) {
            printf("%s is aliased to %s\n", command, tmp->value);
            return 1;
        }
    }
    return 0;
}

int my_which(char **tab, my_stats_t *my_stats)
{
    int count = 0;
    char **path_copy = NULL;
    if (len_array(tab) < 2) {
        printf("which: Too few arguments.\n");
        return 84;
    }
    for (int i = 1;tab[i] != NULL;i++) {
        path_copy = dup_array(my_stats->path);
        if (check_alias_which(tab[i], my_stats) == 1)
            count = 1;
        if (count != 1)
            find_break(tab[i], path_copy);
    }
    return 0;
}
