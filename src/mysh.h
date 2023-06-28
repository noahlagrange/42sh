/*
** EPITECH PROJECT, 2023
** include
** File description:
** mysh
*/

#ifndef MYSH_H_
    #define MYSH_H_

    #include "../include/my.h"
    #include "../include/ast.h"
    #include "../include/list.h"

    #define DEFAULT "\033[0m"
    #define BLACK "\033[0;30m"
    #define RED "\033[0;31m"
    #define GREEN "\033[0;32m"
    #define YELLOW "\033[0;33m"
    #define BLUE "\033[0;34m"
    #define PURPLE "\033[0;35m"
    #define CYAN "\033[0;36m"

    #define INVC "\a\b\n\t\v \0"

    #define CHECK_COND(cond, fd, msg, ret, ...) \
    do { \
        if (cond) { \
            dprintf(fd, msg, __VA_ARGS__); \
            return ret; \
        } \
    } while (0)

typedef struct process_s {
    struct process_s *next;
    pid_t pid;
    char *cmd;
    char *proc;
    int term;
    int status;
} process_t;

typedef struct pipe_s {
    int pipefd[2];
} pipe_t;

typedef struct alias_s {
    char *alias;
    char *value;
} alias_t;

typedef struct command_time_s {
    char *command;
    int hour;
    int min;
    int id;
} command_time_t;

typedef struct history_s {
    list_t *list;
    int n_list;
} history_t;

typedef struct prompt_s {
    char *color_prompt;
    char *color_text;
    int status;
} prompt_t;

typedef struct my_stats_s {
    char **my_env;
    size_t nb_env;
    int index_of_path;
    int index_of_home;
    char **path;
    char *pwd_old;
    char *current_pwd;
    char *home;
    int status;
    char *com;
    list_t *pipesfd;
    list_t *alias;
    history_t *my_history;
    process_t *proc;
    bool is_bg;
    prompt_t *prompt;
    bool exit;
    char **command_exit;
} my_stats_t;

typedef struct build_s {
    char *str;
    int (*func)(char **, my_stats_t *);
} build_t;

typedef struct color_s {
    char *str;
    int (*func)(prompt_t *prompt, int status);
} color_t;

int my_echo(char **tab, my_stats_t *my_stats);
void double_right(my_stats_t *my_stats, ast_t *ast);

process_t *make_process(char *str, int pid);
process_t *add_process(process_t *old, char *str, int pid);
process_t *execute(char *ex, char **agv, process_t *pro, char **env);
///void exe(char *agv);
char *get_str_nbr(int nb);
int do_fg(char **str, my_stats_t *my_stats);
process_t *wait_and_poll(process_t *pro);

char *replace_history(my_stats_t *my_stats, char *command);
char *insert_char(char *str, char add, int n);
int check_history_number(int nb, char *str);
int create_file(ast_t *ast);
int add_file(ast_t *ast);
void redirection_left(my_stats_t *my_stats, ast_t *ast, int (*file)(ast_t *));
ast_t *new_branch(linked_list_t *node);
ast_t *create_ast(linked_list_t *head);
void exec_ast(my_stats_t *my_stats, ast_t *ast);
int no_env(my_stats_t *my_stats);
int check_exit(int nb, int len, char *com, my_stats_t *my_stats);
int sig_child(char *ex, my_stats_t *my_stats, char **arg);
int my_strdup_env(char **env, my_stats_t *my_stats);
void is_path(char *str, my_stats_t *my_stats, int index);
void get_home(my_stats_t *my_stats);
void get_path(my_stats_t *my_stats);
my_stats_t *create_stats(void);
void switch_env(my_stats_t *my_stats);
int change_directory(char *dir, my_stats_t *my_stats);
void go_to_home(my_stats_t *my_stats);
char **del_array(char **tab, my_stats_t *my_stats, int len);
char **append_array(char *tab, my_stats_t *my_stats);
char *add_str(char *s1, char *s2, my_stats_t *my_stats);
int my_exit(char **tab, my_stats_t *my_stats);
int my_cd(char **tab, my_stats_t *my_stats);
int my_print_env(char **tab, my_stats_t *my_stats);
int my_unsetenv(char **tab, my_stats_t *my_stats);
int my_setenv(char **tab, my_stats_t *my_stats);
void add_value(char **tab, my_stats_t *env, int len);
void ex_command(char *ex, char **arg, my_stats_t *my_stats, int i);
void process_child(char **bin, char **arg, my_stats_t *my_stats);
void command_bin(my_stats_t *my_stats, char **arg);
char *separation_of_separator(char *command);
void parser_line(my_stats_t *my_stats, char *command);
void check_command(my_stats_t *my_stats, char **command);
void exec_pipe(my_stats_t *my_stats, ast_t *left, ast_t *right);
void *create_pip(va_list *ap);
void destroy_pip(void *data);
void my_waitpid(my_stats_t *my_stats, pid_t cpid);
int free_stats(my_stats_t *my_stats);
int check_execu(char *com);
history_t *create_history(void);
void add_element_in_history(char *str, history_t *history);
int my_history(char **tab, my_stats_t *my_stats);
int history_flags(my_stats_t *my_stats, char *flags);
void destroy_history(void *data);

int my_where(char **tab, my_stats_t *my_stats);
int check_end_str(char *str, char c);
int my_which(char **tab, my_stats_t *my_stats);
void check_access_path(char *path_command);

int check_color(char **tab, my_stats_t *my_stats);
int my_black(prompt_t *prompt, int status);
int my_yellow(prompt_t *prompt, int status);
int my_green(prompt_t *prompt, int status);
int my_red(prompt_t *prompt, int status);
int my_blue(prompt_t *prompt, int status);
int my_cyan(prompt_t *prompt, int status);
int my_purple(prompt_t *prompt, int status);
int check_input_flag(char *flags);
int check_input_color(char *color[], char *flags);
int check_args_valid(char **tab);
int check_color_valid(char *str);
int change_promt_color(char **tab, my_stats_t *my_stats, color_t COLOR[]);
int change_text_color(char **tab, my_stats_t *my_stats, color_t COLOR[]);
int change_color(char *flags, color_t COLOR[], prompt_t *prompt);

void redirection_right(my_stats_t *my_stats, ast_t *ast, int (*file)
(my_stats_t *my_stats, ast_t *));
int simple_right(my_stats_t *my_stat, ast_t *ast);
int prompt(my_stats_t *my_stats);
list_t *init_alias(my_stats_t *my_stats);
char *is_alias(list_t *list, char *alias);
void *constructor_alias(va_list *ap);
void destroy_alias(void *data);
void add_alias(list_t *list, char *alias, char *value);
int my_alias(char **arr, my_stats_t *my_stats);
char *use_alias(char *command, list_t *list);
char *array_to_str(char **arr);
size_t my_all_arraylen(char **arr);
void print_alias(my_stats_t *my_stats);
char *get_first_word(char *s, char delim);
void pop_array(char **arr, int i);
char *replace_char(char *s, char old, char new);
int my_unalias(char **arr, my_stats_t *my_stats);
int my_repeat(char **arr, my_stats_t *my_stats);
char **manage_star(char **command);
char *get_local_path(char *str);
char *get_pattern(char *str);
char *slice_int(char *str, int i );
void check_alias(char *command, my_stats_t *states);
void change_value(char **tab, my_stats_t *my_stats, int index, int len);
void process_command(my_stats_t *my_stats, char **command, build_t build[]);
char **process_alias(my_stats_t *my_stats, char **command);
int process_builtins(my_stats_t *my_stats, char **arg, build_t builtins[]);
void init_stats(my_stats_t *my_stats);

#endif /* MYSH_H_ */
