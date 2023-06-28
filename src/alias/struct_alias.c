/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** struct_alias
*/
#include "../mysh.h"

/*
    constructor of list_t for alias list
 */
void *constructor_alias(va_list *ap)
{
    alias_t *new = malloc(sizeof(alias_t));
    if (new == NULL)
        return NULL;
    new->alias = va_arg(*ap, char *);
    new->value = va_arg(*ap, char *);
    return new;
}

/*
    destructor of list_t for alias list
 */
void destroy_alias(void *data)
{
    alias_t *gree = data;
    MY_FREE(gree->alias, free);
    MY_FREE(gree, free);
}

/*
    add alias in alphabet order in the list
*/
void add_alias(list_t *list, char *alias, char *value)
{
    linked_list_t *node = NULL;
    alias_t *a = NULL;
    if (list == NULL)
        return;
    LIST_FOREACH_DECL(list->nodes, node, node != NULL && strcmp(CAST(alias_t *
    , node->data)->alias, alias) > 0);
    if (node != NULL) {
        a = CAST(alias_t *, node->data);
        if (strcmp(a->alias, alias) == 0)
            a->value = value;
    } else {
        push_back_list(list, alias, value);
    }
}

/*
    at the start fo the etib shell, this function opens the etibrc if exists
    and configure the etib shell as it's in the config file
*/
list_t *init_alias(my_stats_t *my_stats)
{
    if (my_stats->alias == NULL)
        return NULL;
    char *buf = NULL;
    size_t count = 0;
    FILE *file = fopen(".etibrc", "r");
    if (file == NULL) {
        file = fopen("~/.etibrc", "r");
        if (file == NULL) {
            return my_stats->alias;
        }
    }
    while (getline(&buf, &count, file) > -1) {
        parser_line(my_stats, buf);
        MY_FREE(buf, free);
    }
    return my_stats->alias;
}
