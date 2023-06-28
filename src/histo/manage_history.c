/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** manage_history
*/

#include "../mysh.h"

command_time_t *get_command_by_index(list_t *head, int i)
{
    if (i <= 0)
        return NULL;
    LIST_FOREACH_DECL_BASIC(head->nodes, elem) {
        command_time_t *tmp = CAST(command_time_t *, elem->data);
        if (tmp->id == i)
            return tmp;
    }
    return NULL;
}

char *add_in_command(history_t *his, char *str, char *command, int *i)
{
    if (command[*i + 1] == '\0' || command[*i + 1] == ' ')
        return str;
    if (command[*i + 1] == '!') {
        linked_list_t *elem = get_last_elem(his->list->nodes);
        if (elem == NULL)
            return NULL;
        command_time_t *tmp = CAST(command_time_t *, elem->data);
        str = insert_str(str, tmp->command, *i);
        (*i)++;
    } else {
        int nbr = my_getnbr(command + *i + 1);
        command_time_t *tmp = get_command_by_index(his->list, nbr);
        if (nbr <= 0 || tmp == NULL) {
            mini_printf("%d: Event not found.\n", 2, nbr);
            return NULL;
        }
        str = insert_str(str, tmp->command, *i);
        (*i) += my_lennbr(nbr);
    }
    return str;
}

char *replace_history(my_stats_t *my_stats, char *command)
{
    char *str = NULL;
    bool display = false;
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '!') {
            str = add_in_command(my_stats->my_history, str, command, &i);
            display = true;
        } else {
            str = insert_char(str, command[i], i);
        }
        if (str == NULL)
            return NULL;
    }
    if (display)
        mini_printf("%s\n", 2, str);
    return str;
}

int print_history(list_t *list, int start)
{
    int i = 0;
    if (list->nodes == NULL)
        return 0;
    LIST_FOREACH_DECL_BASIC(list->nodes, elem) {
        if (i >= start) {
            command_time_t *tmp = CAST(command_time_t *, elem->data);
            mini_printf("%d  %d:%d  %s\n", 1, tmp->id, tmp->hour, tmp->min,
            tmp->command);
        }
        i++;
    }
    return 0;
}

int my_history(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    if (len == 1)
        return print_history(my_stats->my_history->list, -1);
    if (len == 2)
        return history_flags(my_stats, tab[1]);
    int number = check_history_number(my_getnbr(tab[1]), tab[1]);
    if (number == -1)
        return 84;
    print_history(my_stats->my_history->list,
    my_stats->my_history->n_list - number);
    return 0;
}
