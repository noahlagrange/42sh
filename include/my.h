/*
** EPITECH PROJECT, 2023
** B-PSU-200-RUN-2-1-minishell1-leo.sautron
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <termios.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <time.h>
    #include <errno.h>
    #include <sys/ioctl.h>

typedef struct flags {
    char c;
    int (*func)(va_list *, int fd);
} flags_t;

char *get_str_nbr(int nb);
char *my_strconcate(char *a, char *b);
char **append(char **array, char *str);
char *my_strchr(char *str, char c);
int my_lennbr(int nb);
char *insert_str(char *str, char *add, int n);
char *slice(char *s, char *del);
int my_strlento(char *s, char *del);
int is_alphanumeric(char c);
char *my_strstr(char *str, char const *to_find);
int check_cd(char *dir);
int check_arg(char **tab);
int mini_printf(char const *format, int fd, ...);
int array_skip(char *c, char **tab);
int my_putstr(char const *str, int fd);
int skip(char c, char *token);
void *my_memset(void *s, size_t i, size_t size);
char **free_path(char **gree);
int skip_array(char *c, char **token);
char **my_str_to_word_array(char *str, char *token);
void free_array(char **array);
char *my_strdup(char const *str);
int my_strlen(char const *str);
int len_array(char **array);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
int my_getnbr(char const *str);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strcat(char *dest, char const *src);
int my_va_putchar(va_list *l, int fd);
int my_putchar(char c, int fd);
int my_printdigits(va_list *l, int fd);
int my_va_putstr(va_list *l, int fd);
int my_va_putchar(va_list *l, int fd);
char **dup_array(char **array);
void *my_calloc(size_t len, size_t size);
int my_strlento_bis(char *s, char *del);
char **my_arrayconcate(char **array, char **array2);
int skip_tab(char *str, char *tokens);

    #define MY_FREE_VA(x, method, ...) \
        do { \
            if ((x) != NULL) { \
                method((x), __VA_ARGS__); \
                (x) = NULL; \
            } \
        } while (0)

    #define MY_FREE(x, method) \
        do { \
            if ((x) != NULL) { \
                method((x)); \
                (x) = NULL; \
            } \
        } while (0)

    #define PRINT_ARRAY(array) \
        do { \
            for (int i = 0; array[i] != NULL; i++) \
                printf("%s\n", array[i]); \
        } while (0)

#endif /* !MY_H_ */
