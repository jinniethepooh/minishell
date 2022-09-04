#include "minishell.h"

// void    *cmd_cleaner_loop(char *src)
// {
//     if (ft_isquotes(*src))
//         return(cmd_cleaner_quotes(src));
//     else if (ft_isredir(*src))
//         return(ft_strdup(src));
//     else if (*src == '$' && ft_strcmp(src, "$"))
//         return (cmd_cleaner_var(src));
//     else
//         return(ft_strdup(src)); // to add having $
// }
// static  char *cmd_cleaner_gen(char *src)
// {
//     t_cmd_loop  g;

//     g.i = 0;
//     g.dst = ft_substr(src, 0, get_cmd_move(&src[g.i]));
// }

void    *cmd_cleaner_loop(char *src)
{
    char    *dst;
    int         i;

    dst = NULL;
    i = 0;
    while (src[i])
    {
        // else if (ft_isredir(src[i]))
        //     i += ft_strlen(ft_strdup(&src[i]));
        if (ft_isquotes(src[i]))
            dst = ft_strjoin(dst, cmd_cleaner_quotes(&src[i]));
        else if (src[i] == '$' && src[i + 1] && !ft_isspace(src[i + 1]))
            dst = ft_strjoin(dst, cmd_cleaner_var(&src[i]));
        else
            dst = ft_strjoin(dst, ft_substr(&src[i], 0, get_cmd_move(&src[i])));
        i += get_cmd_move(&src[i]);
    }
    return (dst);
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