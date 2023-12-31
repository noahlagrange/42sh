/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** my_list
*/

#ifndef LIST_H_
    #define LIST_H_

    #include <stdarg.h>
    #include <stdlib.h>
    #include <stdbool.h>

typedef void* (*constructor_t)(va_list *);
typedef void (*destructor_t)(void *);

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
    struct linked_list_s *prev;
} linked_list_t;

bool push_front_node(linked_list_t **l, constructor_t create, va_list *ap);
linked_list_t *new_node(va_list *ap, constructor_t contructor);
bool push_back_node(linked_list_t **l, constructor_t create, va_list *ap);
void destroy_node(linked_list_t **l, destructor_t destroy);

typedef struct list_s {
    linked_list_t *nodes;
    constructor_t create;
    destructor_t destructor;
} list_t;

linked_list_t *get_last_elem(linked_list_t *head);

bool push_front_list(list_t *l, ...);
void destroy_list(list_t **l);
bool push_back_list(list_t *l, ...);
list_t *create_list(constructor_t constructor, destructor_t destructor);

    #define WHILE_0(d) do { d; } while (0)

    #define LIST_FORWARD(list) (list = list->next)

    #define LIST_FOREACH(list, elem, cond) \
        for (elem = list; cond; LIST_FORWARD(elem))

    #define LIST_FOREACH_BASIC(list, elem) \
        LIST_FOREACH(list, elem, elem)

    #define LIST_FOREACH_NEXT(list, elem) \
        LIST_FOREACH(list, elem, elem->next)

    #define LIST_FOREACH_DECL(list, elem, cond) \
        for (linked_list_t *elem = list; cond; LIST_FORWARD(elem))

    #define LIST_FOREACH_DECL_BASIC(list, elem) \
        LIST_FOREACH_DECL(list, elem, elem)

    #define LIST_FOREACH_DECL_NEXT(list, elem) \
        LIST_FOREACH_DECL(list, elem, elem->next)

    #define LIST_GET_LAST(list, elem) \
        WHILE_0(LIST_FOREACH_NEXT(list, elem) {})

    #define LIST_GET_LAST_DECL(list, elem) \
        linked_list_t *elem = NULL; \
        LIST_GET_LAST(list, elem)

    #define CAST(type, var) ((type)var)

void remove_linked(linked_list_t *l, linked_list_t **head);
void remove_at_index(list_t *l, int index);

linked_list_t *highest_priority(linked_list_t *head);
void parser_command(char *s, list_t *list);

#endif /* !LIST_H_ */
