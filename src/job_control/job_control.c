/*
** EPITECH PROJECT, 2023
** init_job controle
** File description:
** init the struct
*/

#include "../mysh.h"

process_t *make_process(char *str, int pid)
{
    process_t *process = malloc(sizeof(process_t));
    if (process == NULL)
        return NULL;
    process->cmd = strdup(str);
    process->pid = pid;
    process->status = 0;
    process->term = 0;
    process->proc = my_strconcate("/proc/", get_str_nbr(pid));
    process->next = NULL;
    return process;
}

process_t *add_process(process_t *old, char *str, int pid)
{
    process_t *new_pro = old;
    if (old == NULL) {
        return make_process(str, pid);
    }
    for (; old->next != NULL; old = old->next);
    old->next = make_process(str, pid);
    return new_pro;
}

process_t *execute(char *ex, char **arr, process_t *pro, char **env)
{
    process_t *new_pro = pro;
    pid_t child = 0;
    child = fork();
    if (child == 0) {
        MY_FREE(arr[len_array(arr) - 1], free);
        dprintf(0, "%s Started %ld\n",arr[0], (long)getpid());
        arr[0] = ex;
        execve(arr[0], arr, env);
        exit(1);
    } else {
        usleep(10000);
        new_pro = add_process(pro, arr[0], child);
    }
    return new_pro;
}

int do_fg(char **str, my_stats_t *my_stats)
{
    (void)str;
    process_t *pro = my_stats->proc;
    process_t *new_pro;
    int count = 1;
    for (new_pro = pro; new_pro != NULL; new_pro = new_pro->next) {
        printf("[%d]\t%s", count, new_pro->cmd);
        if (new_pro->term == 0)
            printf("is running\n");
        else
            printf("is done\n");
        count += 1;
    }
    return 0;
}

process_t *wait_and_poll(process_t *pro)
{
    DIR *fd;
    process_t *new_pro;
    if (pro == NULL)
        return NULL;
    for (new_pro = pro; new_pro != NULL; new_pro = new_pro->next) {
        waitpid(new_pro->pid, &new_pro->status, WNOHANG);
        fd = opendir(new_pro->proc);
        if (fd == NULL && new_pro->term == 0) {
            new_pro->term = 1;
            printf("%s\t%d\tterminated\n", new_pro->cmd, new_pro->pid);
        }
        closedir(fd);
    }
    return pro;
}
