#include "minishell.h"

static void *cmd_var_gen(char *src, char *dst)
{
    char    *tmp1;
    char    *tmp2;
    int         i;

    i = 0;
    tmp1 = ft_substr(&src[i + 1], 0, ft_loop_until(&src[i + 1], '$', 0));
    tmp2 = mini_getenv(tmp1);
    if (tmp2)
        dst = ft_strjoin(dst, tmp2);
    free(tmp1);
    return (dst);
}

static void *cmd_var_exit(char *src, char *dst)
{
    char    *tmp;
    int         i;

    dst = ft_strjoin(dst, ft_itoa(g_var.exit_status));
    i = 2;
    if (src[i] != '$')
    {
        tmp = ft_substr(&src[i], 0, ft_loop_until(&src[i], '$', 0));
        dst = ft_strjoin(dst, tmp);
        free(tmp);
    }
    return (dst);
}

char *cmd_cleaner_var(char *src)
{
    int         i;
    char    *dst;

    i = 0;
    dst = NULL;
    while (src[i])
    {
        if (src[i + 1] == '?')
        {
            dst = cmd_var_exit(&src[i], dst);
            i += (2 + ft_loop_until(&src[i], '$', 0));
        }
        else
        {
            dst = cmd_var_gen(&src[i], dst);
            i += ft_loop_until(&src[i + 1], '$', 0) + 1;
        }
    }
    return (dst);
}