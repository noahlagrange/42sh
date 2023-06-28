/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** init_history
*/

#include "../mysh.h"

void *contructor_history(va_list *ap)
{
    time_t now = 0;
    struct tm *now_tm = NULL;
    now = time(NULL);
    now_tm = localtime(&now);

    command_time_t *new = malloc(sizeof(command_time_t));
    if (new == NULL)
        return NULL;
    new->command = my_strdup(va_arg(*ap, char *));
    new->id = va_arg(*ap, int);
    new->hour = now_tm->tm_hour;
    new->min = now_tm->tm_min;
    return new;
}

void destroy_history(void *data)
{
    command_time_t *gree = data;
    MY_FREE(gree->command, free);
}

history_t *create_history(void)
{
    history_t *new = malloc(sizeof(history_t));
    if (new == NULL)
        return NULL;
    new->n_list = 0;
    new->list = create_list(contructor_history, destroy_history);
    if (new->list == NULL) {
        MY_FREE(new, free);
        return NULL;
    }
    return new;
}

void replace_in_list(command_time_t *comp)
{
    time_t now = 0;
    struct tm *now_tm = NULL;
    now = time(NULL);
    now_tm = localtime(&now);
    comp->hour = now_tm->tm_hour;
    comp->min = now_tm->tm_min;
    comp->id++;
}

void add_element_in_history(char *str, history_t *history)
{
    char *tmp = my_strdup(str);
    if (tmp == NULL || str[0] == '!')
        return;
    if (history->list->nodes == NULL) {
        push_back_list(history->list, str, 1);
        history->n_list++;
        return;
    }
    linked_list_t *elem = get_last_elem(history->list->nodes);
    command_time_t *comp = CAST(command_time_t *, elem->data);
    int id_tmp = comp->id;
    if (my_strcmp(comp->command, str) == 0)
        return replace_in_list(comp);
    push_back_list(history->list, str, id_tmp + 1);
    history->n_list++;
}
