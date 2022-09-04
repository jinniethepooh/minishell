#include "minishell.h"

static void    *cmd_cleaner_loop(char *src)
{
    if (ft_isquotes(*src))
        return(ft_strdup(src));
    else if (ft_isredir(*src))
        return(ft_strdup(src));
    else if (*src == '$' && ft_strcmp(src, "$"))
        return (cmd_cleaner_var(src));
    else
        return(ft_strdup(src)); // to add having $
}

char    **cmd_cleaner(char **arr)
{
    char    **clean;
    int     i;
    i = 0;
    clean = (char **)malloc((size_2d(arr) + 1) * sizeof(char *));
    while (arr[i])
    {
        clean[i] = cmd_cleaner_loop(arr[i]);
        ++i;
    }
    clean[i] = 0;
    free_2d(arr);
    return (clean);
}