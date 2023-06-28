/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** separation_of_command
*/

#include "mysh.h"

char *append_str(char *str, char c)
{
    int size = my_strlen(str) + 2;
    char *new = NULL;
    new = my_calloc(sizeof(char), size);
    if (new == NULL)
        exit(84);
    int x = 0;
    for (int i = 0; str != NULL && str[i]; i++, x++)
        new[x] = str[i];
    new[x] = c;
    MY_FREE(str, free);
    x++;
    new[x] = '\0';
    return new;
}

int add_space_and_separator(char **new, char *command, int i)
{
    if (i > 0 && skip(command[i - 1], " \t") != 1)
        if ((*new = append_str(*new, ' ')) == NULL)
            exit(84);
    if (command[i] == ';') {
        if ((*new = append_str(*new, ';')) == NULL)
            exit(84);
    }
    for (; command[i] && skip(command[i], "|<>"); i++)
        if ((*new = append_str(*new, command[i])) == NULL)
            exit(84);
    if (skip(command[i], " \t") != 1)
        if ((*new = append_str(*new, ' ')) == NULL)
            exit(84);
    return i;
}

char *separation_of_separator(char *command)
{
    char *new = NULL;
    for (int i = 0; command[i]; i++) {
        if (skip(command[i], "<>|;")) {
            i = add_space_and_separator(&new, command, i);
            continue;
        }
        new = append_str(new, command[i]);
        if (new == NULL)
            exit(84);
    }
    free(command);
    return new;
}
