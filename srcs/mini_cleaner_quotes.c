#include "minishell.h"

char *cmd_cleaner_quotes(char *src)
{
    char    *dst;
    char    *tmp;

    if (*src == '"')
    {
        tmp = ft_substr(&src[1], 0, ft_loop_until(&src[1], src[0], 0));
        dst = cmd_cleaner_loop(tmp, 0);
        free (tmp);
        return (dst);
    }
    else
        return (ft_substr(&src[1], 0, ft_loop_until(&src[1], src[0], 0)));
}