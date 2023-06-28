/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** main
*/

#include "mysh.h"

int process_builtins(my_stats_t *my_stats, char **arg, build_t builtins[])
{
    int i = 0;
    if (arg[0] == NULL)
        return 0;
    for (; builtins[i].func != NULL &&
    my_strcmp(builtins[i].str, arg[0]) != 0; i++);
    if (builtins[i].func == NULL)
        return 0;
    if (my_strcmp(builtins[i].str, "exit") == 0) {
        my_stats->exit = true;
        my_stats->command_exit = dup_array(arg);
        return 1;
    }
    if (builtins[i].func(arg, my_stats))
        my_stats->status = 84;
    else
        my_stats->status = 0;
    return 1;
}

void check_command(my_stats_t *my_stats, char **command)
{
    build_t BUILTINS[] = {
        {"cd", my_cd}, {"exit", my_exit}, {"echo", my_echo},
        {"setenv", my_setenv}, {"env", my_print_env}, {"unsetenv", my_unsetenv}
        , {"history", my_history}, {"alias", my_alias}, {"unalias", my_unalias}
        , {"repeat", my_repeat}, {"color", check_color}, {"where", my_where},
        {"which", my_which}, {"\0", NULL}
    };
    if (command == NULL)
        return (void)mini_printf("Invalid null command.\n", 2);
    command = process_alias(my_stats, command);
    if (command[len_array(command) - 1][0] == '&') {
        command[len_array(command) - 1][0] = '\0';
        my_stats->is_bg = true;
    } else
        my_stats->is_bg = false;
    return process_command(my_stats, command, BUILTINS);
}

void my_bash(my_stats_t *stats)
{
    char *command = NULL;
    size_t len;
    while (1 != 2) {
        if (isatty(0) == 1)
            prompt(stats);
        wait_and_poll(stats->proc);
        if (getline(&command, &len, stdin) == -1)
            return free(command);
        if (len == 0) {
            free(command);
            continue;
        }
        parser_line(stats, command);
        free(command);
        wait_and_poll(stats->proc);
        command = NULL;
        if (stats->exit)
            my_exit(stats->command_exit, stats);
    }
    free(command);
}

int get_info(my_stats_t *my_stats)
{
    if (my_stats->index_of_path != -1)
        get_path(my_stats);
    else {
        if ((my_stats->path = malloc(sizeof(char *))) == NULL)
            exit(84);
        my_stats->path = NULL;
    }
    if (my_stats->index_of_home != -1)
        get_home(my_stats);
    else {
        if ((my_stats->home = malloc(sizeof(char))) == NULL)
            exit(84);
        my_stats->home = NULL;
    }
    my_stats->alias = init_alias(my_stats);
    if (my_stats->alias == NULL)
        exit(84);
    return 0;
}

int main(int ac, char **av, char **env)
{
    (void)av;(void)ac;
    my_stats_t *my_stats = NULL;
    if ((my_stats = create_stats()) == NULL)
        return 84;
    init_stats(my_stats);
    my_stats->nb_env = len_array(env);
    if (my_stats->nb_env == 0) {
        if (no_env(my_stats))
            return 84;
    } else {
        if (my_strdup_env(env, my_stats))
            return 84;
        if (get_info(my_stats) != 0)
            return 84;
    }
    my_bash(my_stats);
    int error = my_stats->status;
    free_stats(my_stats);
    return error;
}
