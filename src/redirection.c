/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** redirection
*/

#include "mysh.h"

int create_file(ast_t *ast)
{
    struct stat st = {0};
    if (ast == NULL || ast->data->type != OP_COMMAND)
        return -1;
    if (stat(ast->data->optional[0], &st) != -1)
        if (S_ISDIR(st.st_mode)) {
            mini_printf("%s: Is a directory.\n", 2, ast->data->optional[0]);
            return -1;
        }
    int fd = open(ast->data->optional[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        mini_printf("%s: Permission denied.\n", 2, ast->data->optional[0]);
        return -1;
    }
    return fd;
}

int add_file(ast_t *ast)
{
    struct stat st = {0};
    if (ast == NULL || ast->data->type != OP_COMMAND)
        return -1;
    if (stat(ast->data->optional[0], &st) != -1)
        if (S_ISDIR(st.st_mode)) {
            mini_printf("%s: Is a directory.\n", 2, ast->data->optional[0]);
            return -1;
        }
    int fd = open(ast->data->optional[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd == -1) {
        mini_printf("%s: Permission denied.\n", 2, ast->data->optional[0]);
        return -1;
    }
    return fd;
}

void redirection_left(my_stats_t *my_stats, ast_t *ast, int (*file)(ast_t *))
{
    int fd = 0;
    int save1 = dup(1);
    if (ast->right == NULL) {
        mini_printf("Missing name for redirect.\n", 2);
        return;
    }
    if ((fd = file(ast->right)) == -1)
        return;
    dup2(fd, 1);
    close(fd);
    exec_ast(my_stats, ast->left);
    dup2(save1, 1);
}
