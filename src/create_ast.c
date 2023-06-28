/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** create_ast
*/

#include "mysh.h"

int my_strlento(char *s, char *del)
{
    int i = 0;
    if (s == NULL)
        return 0;
    for (; s[i]; i++) {
        if ((s[i + 1] != '\0' || s[i + 1] != '&' ) && s[i] == '&')
            continue;
        if (skip(s[i], del))
            return i;
    }
    return i;
}

char *slice(char *s, char *del)
{
    int len = my_strlento(s, del);
    char *new = NULL;
    int j = 0;
    if (skip(s[0], del))
        len = my_strlento_bis(s, del);
    new = my_calloc(sizeof(char), len + 1);
    if (new == NULL)
        return NULL;
    for (; j < len; j++)
        new[j] = s[j];
    new[j] = '\0';
    return new;
}

void parser_command(char *s, list_t *list)
{
    char *new = NULL;
    enum OP type = 0;
    int i = 0;
    while (s[i]) {
        new = slice(s + i, "<>;|&");
        i += strlen(new);
        type = get_type(new);
        if (type != OP_COMMAND) {
            free(new);
            new = NULL;
            push_back_list(list, new, type);
        } else {
            push_back_list(list, new, type);
            free(new);
            new = NULL;
        }
    }
}

enum OP get_type(char *s)
{
    int len = strlen(s);
    if (skip(s[0], "<>;|&")) {
        if (len >= 2 && s[0] == '<' && s[1] == '<')
            return OP_LLEFT;
        if (len >= 2 && s[0] == '>' && s[1] == '>')
            return OP_RRIGHT;
        if (len >= 2 && s[0] == '|' && s[1] == '|')
            return OP_OR;
        if (len >= 2 && s[0] == '&' && s[1] == '&')
            return OP_AND;
        if (s[0] == '<')
            return OP_LEFT;
        if (s[0] == '>')
            return OP_RIGHT;
        if (s[0] == '|')
            return OP_PIPE;
        if (s[0] == ';')
            return OP_SEMICOLON;
    }
    return OP_COMMAND;
}

enum POUNDERATION get_pounderation(enum OP type)
{
    switch (type) {
    case OP_COMMAND:
        return PO_COMMAND;
    case OP_LEFT:
    case OP_LLEFT:
    case OP_RIGHT:
    case OP_RRIGHT:
        return PO_REDIRECTION;
    case OP_SEMICOLON:
        return PO_SEMICOLON;
    case OP_PIPE:
        return PO_PIPE;
    case OP_AND:
    case OP_OR:
        return PO_CONDITIONAL;
    default:
        return PO_COMMAND;
    }
}
