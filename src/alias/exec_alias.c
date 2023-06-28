/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** exec_alias
*/
#include "../mysh.h"

/*
    if alias exists, return the value else return NULL
 */
char *is_alias(list_t *list, char *alias)
{
    alias_t *tmp = NULL;
    LIST_FOREACH_DECL_BASIC(list->nodes, elem) {
        tmp = CAST(alias_t *, elem->data);
        if (strstr(tmp->alias, alias) == NULL)
            continue;
        if (strcmp(tmp->alias, alias) == 0)
            return tmp->value;
    }
    return NULL;
}

void print_alias(my_stats_t *my_stats)
{
    alias_t *tmp = NULL;
    LIST_FOREACH_DECL_BASIC(my_stats->alias->nodes, elem) {
        tmp = CAST(alias_t *, elem->data);
        printf("%s\t%s\n", tmp->alias, tmp->value);
    }
}

int my_alias(char **arr, my_stats_t *my_stats)
{
    if (len_array(arr) < 2 || strcmp(arr[1], "-p") == 0)
        print_alias(my_stats);
    else {
        add_alias(my_stats->alias, arr[1], array_to_str(arr + 2));
    }
    return 0;
}

char *use_alias(char *command, list_t *list)
{
    char **arr = my_str_to_word_array(command, " ");
    char *tmp = NULL;
    if (arr == NULL)
        return NULL;
    for (int i = 0; arr[i]; i++) {
        tmp = is_alias(list, arr[i]);
        if (tmp == NULL)
            continue;
        MY_FREE(arr[i], free);
        arr[i] = tmp;
    }
    return array_to_str(arr);
}

int my_unalias(char **arr, my_stats_t *my_stats)
{
    alias_t *tmp = NULL;
    for (int i = 1; arr[i]; i++) {
        LIST_FOREACH_DECL_BASIC(my_stats->alias->nodes, elem) {
            tmp = CAST(alias_t *, elem->data);
            if (strcmp(arr[i], tmp->alias) == 0)
                remove_linked(elem, &my_stats->alias->nodes);
        }
    }
    return 0;
}
