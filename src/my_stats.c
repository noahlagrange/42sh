/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** my_stats
*/

#include "mysh.h"

int free_stats(my_stats_t *my_stats)
{
    destroy_list(&my_stats->pipesfd);
    free_array(my_stats->my_env);
    free_array(my_stats->path);
    destroy_alias(my_stats->alias);
    free(my_stats->home);
    free(my_stats->pwd_old);
    free(my_stats->prompt);
    free(my_stats);
    return 84;
}

void get_home(my_stats_t *my_stats)
{
    int i = 0;
    for (; my_stats->my_env[my_stats->index_of_home][i] != '\0'; i++)
        if (my_stats->my_env[my_stats->index_of_home][i] == '=')
            break;
    my_stats->home = my_strdup
    (my_stats->my_env[my_stats->index_of_home] + i + 1);
    if (my_stats->home == NULL)
        exit(84);
}

void get_path(my_stats_t *my_stats)
{
    char *tmp = NULL;
    if ((tmp = my_strdup(my_stats->my_env[my_stats->index_of_path])) == NULL)
        exit(84);
    my_stats->path = my_str_to_word_array
    (tmp, "=:");
    free(tmp);
    if (my_stats->path == NULL)
        exit(84);
}

int my_strdup_env(char **env, my_stats_t *my_stats)
{
    my_stats->my_env = malloc(sizeof(char *) * (my_stats->nb_env + 1));
    if (my_stats->my_env == NULL)
        return 1;
    int i = 0;
    for (; env[i]; i++) {
        my_stats->my_env[i] = my_strdup(env[i]);
        if (my_stats->my_env[i] == NULL)
            return 1;
        if (my_strncmp(my_stats->my_env[i], "PATH=", 5) == 0)
            my_stats->index_of_path = i;
        if (my_strncmp(my_stats->my_env[i], "HOME=", 5) == 0)
            my_stats->index_of_home = i;
    }
    my_stats->my_env[i] = NULL;
    return 0;
}

my_stats_t *create_stats(void)
{
    my_stats_t *my_stats = malloc(sizeof(my_stats_t));
    if (my_stats == NULL)
        return NULL;
    my_stats->prompt = calloc(sizeof(prompt_t), 1);
    my_stats->my_env = NULL;my_stats->exit = false;
    my_stats->nb_env = -1;my_stats->command_exit = NULL;
    my_stats->home = NULL;
    my_stats->index_of_home = -1;
    my_stats->index_of_path = -1;
    my_stats->pwd_old = NULL;
    my_stats->status = 0;
    my_stats->pipesfd = NULL;
    my_stats->my_history = create_history();
    my_stats->proc = NULL;
    if (my_stats->my_history == NULL)
        return NULL;
    my_stats->alias = create_list(constructor_alias, destroy_alias);
    return my_stats;
}
