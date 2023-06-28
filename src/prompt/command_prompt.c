/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-42sh-nathan.maillot
** File description:
** command_prompt
*/

#include "../mysh.h"

int change_color(char *flags, color_t COLOR[], prompt_t *prompt)
{
    int i = 0;
    for (;COLOR[i].func != NULL &&
    my_strcmp(COLOR[i].str, flags) != 0; i++);
    if (COLOR[i].func == NULL) {
        return 1;
    }
    if (COLOR[i].func(prompt, prompt->status))
        return 1;
    return 0;
}

int check_color_valid(char *str)
{
    int return_error = 0;
    char *color[] = {
        "--black", "--yellow",
        "--green", "--red",
        "--blue", "--purple",
        "--cyan" , NULL
    };

    if (str == NULL)
        return_error = 1;
    if (check_input_color(color, str) == 1) {
        printf("Invalid Input : --color\n");
        return_error = 1;
    }
    return return_error;
}

void help(void)
{
    char *color[] = {
        "black", "yellow",
        "green", "red",
        "blue", "purple",
        "cyan", NULL
    };
    printf("HOW TO USE:\n");
    printf("\t[--color] -> Set a color for the prompt.\n");
    printf("\t[--full + --color] -> Set a color for the shell.\n");
    printf("ALL COLORS:\n");
    for (int i = 0;color[i] != NULL;i++) {
        printf("\t--%s\n", color[i]);
    }
}

int check_flags(char **tab, my_stats_t *my_stats, color_t COLOR[])
{
    if (len_array(tab) == 2) {
        if (my_strcmp(tab[1], "-h") == 0 || my_strcmp(tab[1], "--help") == 0) {
            help();
            return 0;
        }
        if (check_color_valid(tab[1]) != 1) {
            change_promt_color(tab, my_stats, COLOR);
            return 0;
        }
    }
    if (len_array(tab) == 3) {
        if (check_args_valid(tab) != 1) {
            change_text_color(tab, my_stats, COLOR);
            return 0;
        }
    }
    return 0;
}

int check_color(char **tab, my_stats_t *my_stats)
{
    int len = len_array(tab);
    color_t COLOR[] = {
        {"--black", &my_black},{"--yellow", &my_yellow},
        {"--green", &my_green},
        {"--red", &my_red}, {"--blue", &my_blue},
        {"--purple", &my_purple}, {"--cyan", &my_cyan},
        {"\0", NULL}
    };
    if (len == 1) {
        my_stats->prompt->color_prompt = DEFAULT;
        my_stats->prompt->color_text = DEFAULT;
        return 1;
    }
    if (len > 1) {
        check_flags(tab, my_stats, COLOR);
    }
    return 0;
}
