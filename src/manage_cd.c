/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** manage_cd
*/

#include "mysh.h"

int no_pwd(my_stats_t *my_stats)
{
    char *new_current[] = {"", "PWD", getcwd(NULL, 0), NULL};
    add_value(new_current, my_stats, 3);
    return my_stats->nb_env;
}

void go_to_home(my_stats_t *my_stats)
{
    if (my_stats->home == NULL)
        return (void)mini_printf("cd: No home directory.\n", 2);
    my_stats->pwd_old = getcwd(NULL, 0);
    chdir(my_stats->home);
}

int swap_pwd(my_stats_t *my_stats)
{
    int index = skip_array("PWD", my_stats->my_env);
    if (index == -1)
        index = no_pwd(my_stats);
    chdir(my_stats->pwd_old);
    int i = 0;
    for (; my_stats->my_env[index][i] != '\0'; i++)
        if (my_stats->my_env[index][i] == '=')
            break;
    free(my_stats->pwd_old);
    my_stats->pwd_old = my_strdup(my_stats->my_env[index] + i + 1);
    char *tmp = getcwd(NULL, 0);
    char *new_current[] = {"", "PWD", tmp, NULL};
    change_value(new_current, my_stats, index, 3);
    free(tmp);
    return 0;
}

int change_directory(char *dir, my_stats_t *my_stats)
{
    if (my_strcmp(dir, "-") == 0) {
        if (my_stats->pwd_old == NULL) {
            mini_printf(": No such file or directory.\n", 2);
            return 1;
        }
        return swap_pwd(my_stats);
    }
    if (my_strcmp(dir, "~") == 0) {
        go_to_home(my_stats);
        return 0;
    }
    if (check_cd(dir))
        return 1;
    my_stats->pwd_old = getcwd(NULL, 0);
    chdir(dir);
    return 0;
}

void switch_env(my_stats_t *my_stats)
{
    int index_old = skip_array("OLDPWD", my_stats->my_env);
    int index_current = skip_array("PWD", my_stats->my_env);
    if (index_current == -1)
        return (void)no_pwd(my_stats);
    char *tmp = my_strdup(my_stats->my_env[index_current]);
    if (tmp == NULL)
        exit(free_stats(my_stats));
    char **tab = my_str_to_word_array(tmp, "=");
    if (tab == NULL)
        exit(free_stats(my_stats));
    free(tmp);
    if (index_old != -1) {
        char *new_old[] = {"", "OLDPWD", tab[1], NULL};
        change_value(new_old, my_stats, index_old, 3);
    }
    free_array(tab);
    char *dos = getcwd(NULL, 0);
    char *new_current[] = {"", "PWD", dos, NULL};
    change_value(new_current, my_stats, index_current, 3);
    free(dos);
}
