/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** check_error
*/

#include "mysh.h"

int check_cd(char *dir)
{
    struct stat st = {0};
    int i = stat(dir, &st);
    if (access(dir, X_OK) != -1 && S_ISDIR(st.st_mode))
        return 0;
    if (errno == EACCES || i != -1) {
        if (!S_ISDIR(st.st_mode))
            mini_printf("%s: Not a directory.\n", 2, dir);
        else
            mini_printf("%s: Permission denied.\n", 2, dir);
    } else
        mini_printf("%s: No such file or directory.\n", 2, dir);
    return 1;
}

void is_path(char *str, my_stats_t *my_stats, int index)
{
    free(my_stats->path);
    my_stats->path = my_str_to_word_array(my_strdup(str), "=:");
    if (my_stats->path == NULL)
        exit(free_stats(my_stats));
    my_stats->index_of_path = index;
}

int no_env(my_stats_t *my_stats)
{
    my_stats->my_env = malloc(sizeof(char *) * 1);
    if (my_stats->my_env == NULL)
        return 1;
    my_stats->my_env[0] = NULL;
    my_stats->nb_env = 1;
    return 0;
}

int sig_child(char *ex, my_stats_t *my_stats, char **arg)
{
    if (errno == ENOEXEC)
        mini_printf("%s: Exec format error. Wrong Architecture.\n", 2, ex);
    free_stats(my_stats);
    free_array(arg);
    return 0;
}

int check_arg(char **tab)
{
    char c = tab[1][0];
    int error = 0;
    if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '_')
        return mini_printf
        ("setenv: Variable name must begin with a letter.\n", 2);
    for (int j = 0; tab[1][j] != '\0'; j++)
        error += is_alphanumeric(tab[1][j]);
    if (error > 0)
        return mini_printf("setenv: \
Variable name must contain alphanumeric characters.\n", 2);
    return 0;
}
