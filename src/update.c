/*
** EPITECH PROJECT, 2023
** update
** File description:
** well, real programmers use ed
*/
#include "mysh.h"

void process_command(my_stats_t *my_stats, char **command, build_t b[])
{
    if (process_builtins(my_stats, command, b))
        return;
    command = manage_star(command);
    command_bin(my_stats, command);
}

char **process_alias(my_stats_t *my_stats, char **command)
{
    if (strcmp(command[0], "unalias") != 0 &&
    strcmp(command[0], "alias") != 0) {
        command[0] = use_alias(command[0], my_stats->alias);
        char **tmp = my_str_to_word_array(command[0], INVC);
        command = my_arrayconcate(tmp, command + 1);
    }
    return command;
}

void init_stats(my_stats_t *my_stats)
{
    my_stats->prompt->color_prompt = NULL;
    my_stats->prompt->color_text = NULL;
    my_stats->prompt->status = 0;
}
