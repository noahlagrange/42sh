/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** parser
*/

#include "ast.h"
#include "list.h"
#include "my.h"

void *constructor_parser(va_list *ap)
{
    parser_t *p = malloc(sizeof(parser_t));

    if (p == NULL)
        return NULL;
    p->optional = my_str_to_word_array(va_arg(*ap, char *), "\a\b\n\t\v \0");
    p->type = va_arg(*ap, enum OP);
    return p;
}

void *parser_clone(parser_t *parser)
{
    parser_t *new_parser = malloc(sizeof(parser_t));

    if (new_parser == NULL)
        return NULL;
    new_parser->optional = dup_array(parser->optional);
    new_parser->type = parser->type;
    return new_parser;
}

void destructor_parser(void *data)
{
    parser_t *p = data;

    if (data == NULL)
        return;
    free(p);
}
