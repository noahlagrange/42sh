/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** manage_pipe
*/

#include "mysh.h"

void *create_pip(va_list *ap)
{
    (void)ap;
    pipe_t *pip = my_calloc(sizeof(pid_t), 1);
    if (pip == NULL)
        return NULL;
    if (pipe(pip->pipefd) == -1) {
        MY_FREE(pip, free);
        return NULL;
    }
    return pip;
}

void destroy_pip(void *data)
{
    pipe_t *gree = data;

    close(gree->pipefd[0]);
    close(gree->pipefd[1]);
    free(gree);
}

static int check_error_pipe(my_stats_t *my_stats, ast_t *left, ast_t *right)
{
    if (left == NULL || right == NULL) {
        my_stats->status = 84;
        return 1;
    }
    if (my_stats->pipesfd == NULL)
        if ((my_stats->pipesfd = create_list(create_pip, destroy_pip))
        == NULL) {
            my_stats->status = 84;
            return 1;
        }
    if (push_back_list(my_stats->pipesfd) == false)
        exit(84);
    return 0;
}

void exec_pipe(my_stats_t *my_stats, ast_t *left, ast_t *right)
{
    pid_t pid;
    if (check_error_pipe(my_stats, left, right))
        return (void)mini_printf("Invalid null command.\n", 2);
    LIST_GET_LAST_DECL(my_stats->pipesfd->nodes, elem);
    pipe_t *tmp = CAST(pipe_t *, elem->data);
    if ((pid = fork()) == 0) {
        dup2(tmp->pipefd[1], 1);
        close(tmp->pipefd[1]);
        exec_ast(my_stats, left);
        exit(my_stats->status);
    } else {
        dup2(tmp->pipefd[0], 0);
        close(tmp->pipefd[1]);
        exec_ast(my_stats, right);
        my_waitpid(my_stats, pid);
    }
}
