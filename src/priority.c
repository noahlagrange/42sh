/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** priority
*/

#include "mysh.h"

void excute_line(my_stats_t *my_stats, list_t *parse)
{
    ast_t *ast = create_ast(parse->nodes);
    if (ast == NULL)
        return;
    destroy_list(&parse);
    exec_ast(my_stats, ast);
    destroy_list(&my_stats->pipesfd);
    destroy_ast(&ast);
}

void parser_line(my_stats_t *my_stats, char *command)
{
    int save1 = dup(1);
    int save0 = dup(0);
    if (command == NULL || my_strcmp(command, "\n") == 0)
        return;
    command[my_strlen(command) - 1] = '\0';
    command = replace_history(my_stats, command);
    if (command == NULL)
        return;
    add_element_in_history(command, my_stats->my_history);
    my_stats->com = command;
    list_t *parse = create_list(constructor_parser, destructor_parser);
    parser_command(command, parse);
    excute_line(my_stats, parse);
    dup2(save0, 0);
    dup2(save1, 1);
}
