#include "minishell.h"

static char *cmd_var_gen(char *src)
{
    int     i;
    char    *tmp;
    char    *dst;

    i = get_cmd_move(src) - 1;
    tmp = ft_substr(src + 1, 0, i);
    dst = mini_getenv(tmp);
    free (tmp);
    return (dst);
}

char    *cmd_cleaner_var(char *src)
{
    if (*(src + 1) == '?')
        return (ft_itoa(g_var.exit_status));
    else
        return (cmd_var_gen(src));
}