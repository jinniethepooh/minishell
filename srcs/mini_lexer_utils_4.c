#include "minishell.h"

static int  get_arr_size(char **arr)
{
    int sz;

    sz = 0;
    while (arr[sz])
        ++sz;
    return (sz);
}

static void *cmd_cleaner_var(char *src)
{
    char    *tmp;
    char    *dst;
    int     i;

    i = 0;
    tmp = ft_strjoin(src + 1, "=");
    while (g_var.env[i] && ft_strncmp(tmp, g_var.env[i], ft_strlen(tmp)))
        ++i;
    if (!ft_strncmp(tmp, g_var.env[i], ft_strlen(tmp)))
        dst = ft_substr(g_var.env[i], ft_strlen(tmp), ft_strlen(g_var.env[i]));
    else
        dst = ft_strdup("\n");
    free(tmp);
    return (dst);
}

static void    *cmd_cleaner_loop(char *src)
{
    if (ft_isquotes(*src))
        printf("q\n");
    else if (ft_isredir(*src))
        printf("r\n");
    else if (*src == '$' && ft_strcmp(src, "$"))
        return (cmd_cleaner_var(src));
    else
        return(ft_strdup(src));
    return (NULL);
}

char    **cmd_cleaner(char **arr)
{
    char    **clean;
    int     i;
    i = 0;
    clean = (char **)malloc((get_arr_size(arr) + 1) * sizeof(char *));
    while (arr[i])
    {
        clean[i] = cmd_cleaner_loop(arr[i]);
        ++i;
    }
    clean[i] = 0;
    free_2d(arr);
    return (clean);
}