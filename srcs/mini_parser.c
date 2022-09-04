#include "minishell.h"

static void	mini_split_getenv(char **arg);
static char	*mini_substitute_env(char *arg);

void	mini_parser_env(char **arg)
{
	char	**before;
	char	**after;
	char	*temp;
	int		size;
	int		i;
	int		j;

	if (!ft_strchr(*arg, '$'))
		return ;
	before = ft_split(*arg + pos_in_str(*arg, '$'), '$');
	if (size_2d(before) == 0)
		return ;
	after = dup_2d(before);
	map_2d(&after, &mini_split_getenv);
	size = pos_in_str(*arg, '$') + count_in_str(*arg, '$') - size_2d(before) + 1;
	i = 0;
	while (after[i])
		size += ft_strlen(after[i++]);
	temp = calloc(size, sizeof(*temp));
	i = 0;
	j = 0;
	while ((*arg)[i])
	{
		*temp++ = (*arg)[i];
		if ((*arg)[i++] == '$')
		{
			if (ft_strncmp(*arg + i, before[j], ft_strlen(before[j])) == 0)
			{
				strcpy(--temp, after[j]);
				temp += ft_strlen(after[j]);
				i += ft_strlen(before[j++]);
			}
		}
	}
	free_2d(before);
	free_2d(after);
	free(*arg);
	*arg = temp - size + 1;
}

static void	mini_split_getenv(char **arg)
{
	char	*val;
	char	*new;
	int		i;

	i = 0;
	val = mini_substitute_env(*arg);
	while ((*arg)[i] && ft_isalnum((*arg)[i]))
		i++;
	if (i == 0 && (*arg)[i] == '?')
		i++;
	new = ft_strjoin(val, *arg + i);
	free(*arg);
	*arg = new;
}

static char	*mini_substitute_env(char *arg)
{
	char	*val;
	char	*temp;
	int		i;

	if (*arg == '?')
		return (ft_itoa(g_var.exit_status));
	i = 0;
	while (arg[i] && !ft_isalnum(arg[i]))
		i++;
	if (!arg[i])
		return (ft_strdup("$"));
	i = 0;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	temp = ft_substr(arg, 0, i);
	val = mini_getenv(temp);
	free(temp);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}
