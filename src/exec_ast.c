/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** exec_ast
*/

#include "mysh.h"

void exec_semicolon(my_stats_t *stats, ast_t *ast)
{
    exec_ast(stats, ast->left);
    destroy_list(&stats->pipesfd);
    exec_ast(stats, ast->right);
    destroy_list(&stats->pipesfd);
}

void exec_and(my_stats_t *stats, ast_t *ast)
{
    exec_ast(stats, ast->left);
    destroy_list(&stats->pipesfd);
    if (stats->status != 0)
        return;
    exec_ast(stats, ast->right);
    destroy_list(&stats->pipesfd);
}

void exec_or(my_stats_t *stats, ast_t *ast)
{
    exec_ast(stats, ast->left);
    destroy_list(&stats->pipesfd);
    if (stats->status == 0)
        return;
    exec_ast(stats, ast->right);
    destroy_list(&stats->pipesfd);
}

void exec_ast2(my_stats_t *my_stats, ast_t *ast)
{
    switch (ast->data->type) {
    case OP_PIPE:
        exec_pipe(my_stats, ast->left, ast->right);
        return;
    case OP_SEMICOLON:
        exec_semicolon(my_stats, ast);
        return;
    case OP_AND:
        exec_and(my_stats, ast);
        return;
    case OP_OR:
        exec_or(my_stats, ast);
        return;
    case OP_LLEFT:
        double_right(my_stats, ast);
        return;
    default:
        return;
    }
}

void exec_ast(my_stats_t *my_stats, ast_t *ast)
{
    if (ast == NULL)
        return;
    switch (ast->data->type) {
    case OP_COMMAND:
        check_command(my_stats, ast->data->optional);
        return;
    case OP_LEFT:
        redirection_right(my_stats, ast, simple_right);
        return;
    case OP_RRIGHT:
        redirection_left(my_stats, ast, add_file);
        return;
    case OP_RIGHT:
        redirection_left(my_stats, ast, create_file);
        return;
    default:
        return exec_ast2(my_stats, ast);
    }
}
