#include "minishell.h"

void	*cmd_cleaner_loop(char *src, int flag)
{
	char	*dst;
	int		i;

	dst = NULL;
	i = 0;
	//if (ft_strchr(src, '$'))
	//	return (ft_strdup(src));
	while (src[i])
    {
        if (ft_isquotes(src[i]) && flag)
            dst = ft_strjoin(dst, cmd_cleaner_quotes(&src[i]));
        else if (src[i] == '$' && get_var_skip(src[i + 1]))
            dst = ft_strjoin(dst, cmd_cleaner_var(&src[i]));
        else
            dst = ft_strjoin(dst, ft_substr(&src[i], 0, get_cmd_move(&src[i], flag)));
        i += get_cmd_move(&src[i], flag);
    }
    return (dst);
}

char	**cmd_cleaner(char **arr)
{
	char	**clean;
	int	 i;

	i = 0;
	clean = (char **)malloc((size_2d(arr) + 1) * sizeof(char *));
	while (arr[i])
	{
		clean[i] = cmd_cleaner_loop(arr[i], 1);
		++i;
	}
	clean[i] = 0;
	free_2d(arr);
	return (clean);
}