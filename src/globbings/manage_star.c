/*
** EPITECH PROJECT, 2023
** src/globbings/manage_star
** File description:
** you're a bad developer
*/
#include "../mysh.h"

char *slice_int(char *str, int i)
{
    char *new_str = malloc(sizeof(char) * (i + 1));
    int j = 0;

    for (j = 0; j < i; j++)
        new_str[j] = str[j];
    new_str[j] = '\0';
    return new_str;
}

char **replace_star(char **command, char **star, int i, int len)
{
    char **new = malloc(sizeof(char *) * (i + len + 1));
    int j = 0;
    for (j = 0; j < i; j++)
        new[j] = strdup(command[j]);
    for (int k = 0; k < len; k++) {
        new[j] = strdup(star[k]);
        j++;
    }
    new[j] = NULL;
    return new;
}

char **add_star(char **star, char *str, char *path)
{
    int len = len_array(star);
    star = realloc(star, sizeof(char *) * (len + 2));
    star[len] = calloc(sizeof(char), (strlen(path) + strlen(str) + 2));
    if (strcmp(path, ".") != 0) {
        star[len] = strcpy(star[len], path);
        star[len] = strcat(star[len], "/");
    }
    star[len] = strcat(star[len], str);
    star[len] = strcat(star[len], "\0");
    star[len + 1] = NULL;
    return star;
}

char **globbing(char **command, int i)
{
    char *path = get_local_path(command[i]);
    char *pattern = get_pattern(command[i]);
    char **star = malloc(sizeof(char *) * 1);
    if (star == NULL)
        return command;
    star[0] = NULL;
    DIR *dir = opendir(path);
    if (dir == NULL)
        return command;
    struct dirent *dirent = {0};
    int len = 0;
    while ((dirent = readdir(dir)) != NULL) {
        if (dirent->d_name[0] == '.')
            continue;
        if (fnmatch(pattern, dirent->d_name, FNM_PATHNAME) == 0) {
            star = add_star(star, dirent->d_name, path);
            len++;
        }
    } command = replace_star(command, star, i, len);
    return command;
}

char **manage_star(char **command)
{
    int i = 1;
    for (i = 1; command[i]; i++) {
        if (skip_tab(command[i], "*?")) {
            command = globbing(command, i);
            break;
        }
    }
    return command;
}
