#include "minishell.h"

// ' not interpret
// " interpret

char *cmd_cleaner_quotes(char *src)
{
    int         i;
    char    *dst;

    i = 0;
    dst = NULL;
    while (src[i])
    {
        if (src[i] == '"')
            printf("\"\n");
        if (src[i] == '\'')
            printf("\'\n");
    }
    return (dst);
}