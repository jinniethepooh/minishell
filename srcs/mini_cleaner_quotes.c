#include "minishell.h"

// ' not interpret
// " interpret

char *cmd_cleaner_quotes(char *src)
{
    // char    *dst;
    int         i;

    // dst = NULL;
    i = 0;
    if (src[i] == '"')
        return (src);
    else
        return (ft_substr(&src[i + 1], 0, ft_loop_until(&src[i + 1], src[i], 0)));
}