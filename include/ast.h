/*
** EPITECH PROJECT, 2023
** ast
** File description:
** ast
*/

#ifndef AST_H_
    #define AST_H_
    #include <criterion/criterion.h>
    #include <dirent.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <fnmatch.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <unistd.h>

    enum OP get_type(char *s);

enum OP {
    OP_COMMAND,
    OP_LEFT,
    OP_LLEFT,
    OP_RIGHT,
    OP_RRIGHT,
    OP_PIPE,
    OP_SEMICOLON,
    OP_AND,
    OP_OR,
};

enum POUNDERATION {
    PO_COMMAND,
    PO_REDIRECTION,
    PO_LEFT = PO_REDIRECTION,
    PO_LLEFT = PO_REDIRECTION,
    PO_RIGHT = PO_REDIRECTION,
    PO_RRIGHT = PO_REDIRECTION,
    PO_PIPE,
    PO_CONDITIONAL,
    PO_AND = PO_CONDITIONAL,
    PO_OR = PO_CONDITIONAL,
    PO_SEMICOLON
};

typedef struct parser_s {
    enum OP type;
    char **optional;
} parser_t;

typedef struct ast_s {
    parser_t *data;
    struct ast_s *left;
    struct ast_s *right;
} ast_t;

enum POUNDERATION get_pounderation(enum OP type);
void destroy_ast(ast_t **gree);

void *constructor_parser(va_list *ap);
void *parser_clone(parser_t *parser);
void destructor_parser(void *data);


#endif /* !AST_H_ */
