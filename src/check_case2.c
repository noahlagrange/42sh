/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell2-leo.sautron
** File description:
** check_case2
*/

#include "mysh.h"

int check_execu(char *com)
{
    struct stat st = {0};
    if (stat(com, &st) == -1)
        return 1;
    if (S_ISDIR(st.st_mode)) {
        mini_printf("%s: Permission denied.\n", 2, com);
        return 0;
    }
    return 1;
}
