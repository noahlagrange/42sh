/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** child_proc
*/

#include "mysh.h"

int check_ex(int status)
{
    if (WTERMSIG(status) == 11)
        mini_printf("Segmentation fault", 2);
    if (WTERMSIG(status) == SIGFPE)
        mini_printf("Floating exception", 2);
    if (WTERMSIG(status) == SIGABRT)
        mini_printf("Abort", 2);
    if (WTERMSIG(status) == SIGBUS)
        mini_printf("Bus error", 2);
    if (WTERMSIG(status) == SIGSYS)
        mini_printf("Bad system call", 2);
    if (WTERMSIG(status) == SIGTRAP)
        mini_printf("Trace/BPT trap", 2);
    if (WTERMSIG(status) == SIGILL)
        mini_printf("Illegal instruction", 2);
    if (WCOREDUMP(status))
        mini_printf(" (core dumped)\n", 2);
    else
        mini_printf("\n", 2);
    return 84;
}

void my_waitpid(my_stats_t *my_stats, pid_t cpid)
{
    int wstatus = 0;
    int w = 0;
    do {
        w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1)
            break;
        if (WIFSIGNALED(wstatus))
            check_ex(wstatus);
    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

    my_stats->status = WSTOPSIG(wstatus) ? 84 : 0;
}

void ex_command(char *ex, char **arg, my_stats_t *my_stats, int i)
{
    pid_t child = fork();
    if (child == 0) {
        if (i)
            free(arg[0]);
        arg[0] = ex;
        execve(ex, arg, my_stats->my_env);
        sig_child(ex, my_stats, arg);
        free_stats(my_stats);
        exit(1);
    } else
        my_waitpid(my_stats, child);
    return;
}

void process_child(char **bin, char **arg, my_stats_t *my_stats)
{
    char *ex = NULL;

    for (int i = 1; bin[i]; i++) {
        int size = my_strlen(bin[i]) + my_strlen(arg[0]) + 2;
        ex = malloc(sizeof(char) * (size));
        if (ex == NULL)
            exit(free_stats(my_stats));
        ex = my_memset(ex, 0, size);
        my_strcat(my_strcat(my_strcat(ex, bin[i]), "/"), arg[0]);
        if (access(ex, X_OK) != -1 && my_stats->is_bg) {
            my_stats->proc = execute(ex, arg, my_stats->proc, my_stats->my_env);
            return;
        } if (access(ex, X_OK) != -1)
            return ex_command(ex, arg, my_stats, 1);
        free(ex);
    }
    my_stats->status = 84;
    mini_printf("%s: Command not found.\n", 2, arg[0]);
}

void command_bin(my_stats_t *my_stats, char **arg)
{
    if (check_execu(arg[0]) == 0) {
        my_stats->status = 84;
        return;
    }
    if (access(arg[0], X_OK) != -1) {
        ex_command(arg[0], arg, my_stats, 0);
    } else if (my_stats->index_of_path == -1) {
        mini_printf("%s: Command not found.\n", 2, arg[0]);
        my_stats->status = 84;
    } else
        process_child(my_stats->path, arg, my_stats);
}
