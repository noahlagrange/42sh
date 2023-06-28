/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** command
*/

#include "mysh.h"

int my_cd(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    if (len == 1)
        go_to_home(my_stats);
    if (len == 2) {
        if (change_directory(tab[1], my_stats)) {
            return 1;
        }
    }
    if (len >= 3) {
        write(2, "cd: Too many arguments.\n", 24);
        my_stats->status = 84;
        return 1;
    }
    switch_env(my_stats);
    return 0;
}

int my_exit(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    if (len == 1) {
        free(my_stats->com);
        free_stats(my_stats);
        mini_printf("exit\n", 1);
        free_array(tab);
        exit(0);
    }
    int nb = my_getnbr(tab[1]);
    if (check_exit(nb, len, tab[1], my_stats))
        return 1;
    free(my_stats->com);
    free_stats(my_stats);
    mini_printf("exit\n", 1);
    free_array(tab);
    exit(nb);
    return 0;
}

int my_print_env(char **tab, my_stats_t *my_stats)
{
    if (len_array(tab) > 1) {
        my_stats->status = 2;
        write(2, "env: Expression Syntax.\n", 24);
        return 1;
    }
    for (int i = 0; my_stats->my_env[i]; i++) {
        write(1, my_stats->my_env[i], my_strlen(my_stats->my_env[i]));
        write(1 , "\n", 1);
    }
    return 0;
}

int my_unsetenv(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    if (len == 1)
        return write(2, "unsetenv: Too few arguments.\n", 29);
    for (int i = 1; tab[i]; i++) {
        if (skip_array(tab[i], my_stats->my_env) != -1)
            continue;
        len--;
    }
    if (len == 1)
        return 0;
    char **new = del_array(tab, my_stats, len - 1);
    free_array(my_stats->my_env);
    my_stats->my_env = NULL;
    my_stats->my_env = new;
    my_stats->nb_env -= (len - 1);
    return 0;
}

int my_setenv(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    int index = 0;
    if (len == 1)
        return my_print_env(tab, my_stats);
    if (len > 3)
        return write(2, "setenv: Too many arguments.\n", 28);;
    if (check_arg(tab) != 0)
        return 1;
    if ((index = skip_array(tab[1], my_stats->my_env)) != -1)
        change_value(tab, my_stats, index, len);
    else {
        add_value(tab, my_stats, len);
        my_stats->nb_env++;
    }
    return 0;
}
