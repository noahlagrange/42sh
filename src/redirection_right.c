/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** redirection_right
*/

#include "mysh.h"

void manage_double_right(int *pipefd, my_stats_t *my_stats, ast_t *ast,
char *str)
{
    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        exec_ast(my_stats, ast->left);
        exit(0);
    } else {
        close(pipefd[0]);
        if (str != NULL)
            write(pipefd[1], str, strlen(str));
        close(pipefd[1]);
        my_waitpid(my_stats, pid);
    }
    dup2(0, pipefd[0]);
    close(pipefd[0]);
    close(pipefd[1]);
}

void double_right(my_stats_t *my_stats, ast_t *ast)
{
    if (ast->right == NULL || ast->right->data->type != OP_COMMAND ||
    ast->left == NULL) {
        mini_printf("Missing name for redirect.\n", 2);
        return;
    }
    char *stop = ast->right->data->optional[0];
    char *buff = NULL;
    size_t size = 0;
    int pipefd[2] = {0};
    pipe(pipefd);
    char *str = NULL;
    while (true) {
        mini_printf("? ", 0);
        if (getline(&buff, &size, stdin) < 0)
            break;
        if (strncmp(buff, stop, strlen(stop)) == 0
        && strlen(buff) - 1 == strlen(stop))
            break;
        str = my_strconcate(str, buff);
    } return manage_double_right(pipefd, my_stats, ast, str);
}

int simple_right(my_stats_t *my_stats, ast_t *ast)
{
    if (ast == NULL || ast->data->type != OP_COMMAND)
        return -1;
    int fd = open(ast->data->optional[0], O_RDONLY);
    if (fd == -1) {
        my_stats->status = 84;
        return -1;
    }
    return fd;
}

void redirection_right(my_stats_t *my_stats, ast_t *ast, int (*file)
(my_stats_t *my_stats, ast_t *))
{
    int fd = 0;
    if (ast->right == NULL) {
        mini_printf("Missing name for redirect.\n", 2);
        return;
    }
    if ((fd = file(my_stats, ast->right)) == -1)
        return (void)mini_printf("%s: No such file or directory.\n", 2,
        ast->right->data->optional[0]);
    dup2(fd, 0);
    close(fd);
    exec_ast(my_stats, ast->left);
    dup2(0, fd);
    close(fd);
}
