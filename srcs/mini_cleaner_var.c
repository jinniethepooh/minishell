#include "minishell.h"

static char *cmd_var_gen(char *src)
{
    t_cmd_loop  v;

    v.i = get_cmd_move(src) - 1;
    v.tmp = ft_substr(src + 1, 0, v.i);
    v.dst = mini_getenv(v.tmp);
    free (v.tmp);
    return (v.dst);
}

char    *cmd_cleaner_var(char *src)
{
    if (*(src + 1) == '?')
        return (ft_itoa(g_var.exit_status));
    else
        return (cmd_var_gen(src));
}