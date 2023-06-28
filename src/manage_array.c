/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** manage_array
*/

#include "mysh.h"

void change_value(char **tab, my_stats_t *my_stats, int index, int len)
{
    char *str = NULL;
    free(my_stats->my_env[index]);
    my_stats->my_env[index] = NULL;
    if (len == 2)
        str = add_str(tab[1], NULL, my_stats);
    else
        str = add_str(tab[1], tab[2], my_stats);
    my_stats->my_env[index] = str;
    if (my_strcmp(tab[1], "PATH") == 0)
        is_path(str, my_stats, index);
}

char **del_array(char **tab, my_stats_t *my_stats, int len)
{
    char **new = malloc(sizeof(char *) * (my_stats->nb_env - len + 1));
    if (new == NULL)
        exit(84);
    int x = 0;
    for (int i = 0; my_stats->my_env[i]; i++) {
        if (array_skip(my_stats->my_env[i], tab) != -1)
            continue;
        if ((new[x] = my_strdup(my_stats->my_env[i])) == NULL)
            return NULL;
        x++;
    }
    new[x] = NULL;
    return new;
}

char **append_array(char *tab, my_stats_t *my_stats)
{
    char **new = malloc(sizeof(char*) * (my_stats->nb_env + 2));
    if (new == NULL) {
        free_stats(my_stats);
        exit(84);
    }
    int x = 0;
    for (int i = 0; my_stats->my_env[i] != NULL; i++) {
        if ((new[x] = my_strdup(my_stats->my_env[i])) == NULL)
            exit(84);
        x++;
    }
    new[x] = my_strdup(tab);
    new[x + 1] = NULL;
    return new;
}

char *add_str(char *s1, char *s2, my_stats_t *my_stats)
{
    int size = my_strlen(s1) + my_strlen(s2) + 2;
    char *new = malloc(sizeof(char) * (size));
    if (new == NULL)
        exit(free_stats(my_stats));
    new = my_memset(new, 0, size);
    my_strcat(new, s1);
    my_strcat(new, "=");
    my_strcat(new, s2);
    return new;
}

void add_value(char **tab, my_stats_t *env, int len)
{
    char *str = NULL;
    if (len == 2)
        str = add_str(tab[1], NULL, env);
    else
        str = add_str(tab[1], tab[2], env);
    char **new = append_array(str, env);
    free_array(env->my_env);
    env->my_env = NULL;
    env->my_env = new;
    if (my_strcmp(tab[1], "PATH") == 0)
        is_path(str, env, env->nb_env - 1);
    free(str);
}
