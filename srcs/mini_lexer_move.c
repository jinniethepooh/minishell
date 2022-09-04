#include "minishell.h"

int get_var_skip(char c)
{
    return (!(c == '\0' || c == '$' || ft_isquotes(c) || ft_isspace(c)));
}

static int  get_quo_move(char *s)
{
    return (ft_loop_until(s + 1, *s, 0) + 2);
}

static int  get_var_move(char *s)
{
    int     len;

    len = 1;
    if (s[len] == '?')
        return (2);
    else
    {
        while (get_var_skip(s[len]))
            len++;
        return (len);
    }
}

int  get_cmd_move(char *s)
{
    int len;

    len = 0;
    if (ft_isquotes(s[len]))
        return (get_quo_move(s));
    else if (s[len] == '$')
        return (get_var_move(s));
    else
    {
        while (s[len] && s[len] != '$' && !ft_isquotes(s[len]))
            len++;
    }
    return (len);
}