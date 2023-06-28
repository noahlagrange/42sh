/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** ast
*/

#include "mysh.h"

linked_list_t *highest_priority(linked_list_t *head)
{
    linked_list_t *list = head;
    linked_list_t *tmp = head;
    while (tmp != NULL) {
        if (get_pounderation(CAST(parser_t *, tmp->data)->type) >=
        get_pounderation(CAST(parser_t *, list->data)->type))
            list = tmp;
        tmp = tmp->next;
    }
    return list;
}

ast_t *new_branch(linked_list_t *node)
{
    if (node == NULL)
    return NULL;
    ast_t *branch = malloc(sizeof(ast_t));
    if (branch == NULL)
        return NULL;
    branch->data = parser_clone(node->data);
    if (branch->data == NULL) {
        free(branch);
        return NULL;
    }
    branch->left = NULL;
    branch->right = NULL;
    return branch;
}

ast_t *create_ast(linked_list_t *head)
{
    ast_t *ast = NULL;
    linked_list_t *list = highest_priority(head);

    if (list == head) {
        ast = new_branch(list);
        if (ast == NULL)
            return NULL;
        return ast;
    } else {
        ast = new_branch(list);
        ast->right = create_ast(list->next);
        list->prev->next = NULL;
        ast->left = create_ast(head);
        list->prev->next = list;
    }
    return ast;
}

void destroy_ast(ast_t **gree)
{
    if (*gree == NULL)
        return;
    destroy_ast(&(*gree)->left);
    destroy_ast(&(*gree)->right);
    destructor_parser((*gree)->data);
    free(*gree);
}
