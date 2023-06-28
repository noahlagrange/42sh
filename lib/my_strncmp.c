/*
** EPITECH PROJECT, 2022
** oui
** File description:
** oui
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (n < 0) {
        return 0;
    }
    while (i < n) {
        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        } else {
            i++;
        }
    }
    return 0;
}
