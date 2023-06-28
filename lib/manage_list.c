/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** manage_list
*/
#include "ast.h"
#include "list.h"
#include "my.h"

linked_list_t *get_last_elem(linked_list_t *head)
{
    linked_list_t *elem = NULL;
    if (head == NULL)
        return NULL;
    LIST_FOREACH_NEXT(head, elem);
    if (elem == NULL)
        return head;
    return elem;
}

void remove_linked(linked_list_t *l, linked_list_t **head)
{
    linked_list_t *tmp = l;
    if (tmp == *head)
        *head = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
}

void remove_at_index(list_t *l, int index)
{
    int i = 0;
    LIST_FOREACH_DECL_BASIC(l->nodes, elem) {
        if (index == i)
            return remove_linked(elem, &l->nodes);
        i++;
    }
}
