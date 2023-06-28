/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** where
*/

#include "mysh.h"

int check_end_str(char *str, char c)
{
    int end_str = my_strlen(str);
    if (str[end_str - 1] == c) {
        return 1;
    }
    return 0;
}

void check_access_path_where(char *path_command)
{
    if (access(path_command, X_OK) != -1) {
        printf("%s\n", path_command);
    }
}

void find(char *command, char **path)
{
    for (int i = 1;path[i] != NULL;i++) {
        if (check_end_str(path[i], '/') == 0) {
            strcat(strcat(path[i], "/"), command);
            check_access_path_where(path[i]);
        }
    }
}

void check_alias(char *command, my_stats_t *states)
{
    alias_t *tmp = NULL;
    LIST_FOREACH_DECL_BASIC(states->alias->nodes, elem) {
        tmp = CAST(alias_t *, elem->data);
        if (my_strcmp(command, tmp->alias) == 0)
            printf("%s is aliased to %s\n", command, tmp->value);
    }
}

int my_where(char **tab, my_stats_t *my_stats)
{
    char **path_copy = NULL;
    if (len_array(tab) < 2) {
        printf("where: Too few arguments.\n");
        return 84;
    }
    for (int i = 1;tab[i] != NULL;i++) {
        path_copy = dup_array(my_stats->path);
        check_alias(tab[i], my_stats);
        find(tab[i], path_copy);
    }
    return 0;
}
