#include "minishell.h"

static void	parse_each(char **arg);
static char	*substitute_each(char *arg);
static char	*get_parsed_arg(char *arg, char **before, char **after);

void	mini_parser_env(char **arg)
{
	char	**before;
	char	**after;
	char	*temp;

	if (!ft_strchr(*arg, '$'))
		return ;
	before = ft_split(*arg + pos_in_str(*arg, '$'), '$');
	if (size_2d(before) == 0)
		return ;
	after = dup_2d(before);
	map_2d(&after, &parse_each);
	temp = get_parsed_arg(*arg, before, after);
	free(*arg);
	*arg = temp;
	free_2d(before);
	free_2d(after);
}

static char	*get_parsed_arg(char *arg, char **before, char **after)
{
	char	*temp;
	int		size;
	int		i;

	size = pos_in_str(arg, '$') + count_in_str(arg, '$') - size_2d(before) + 1;
	i = 0;
	while (after[i])
		size += ft_strlen(after[i++]);
	temp = calloc(size, sizeof(*temp));
	i = 0;
	while (arg[i])
	{
		*temp++ = arg[i];
		if (arg[i++] == '$')
		{
			if (ft_strncmp(arg + i, *before, ft_strlen(*before)) == 0)
			{
				strcpy(--temp, *after);
				temp += ft_strlen(*after++);
				i += ft_strlen(*before++);
			}
		}
	}
	return (temp - size + 1);
}

static void	parse_each(char **arg)
{
	char	*val;
	char	*new;
	int		i;

	i = 0;
	val = substitute_each(*arg);
	while ((*arg)[i] && ft_isalnum((*arg)[i]))
		i++;
	if (i == 0 && (*arg)[i] == '?')
		i++;
	new = ft_strjoin(val, *arg + i);
	free(*arg);
	*arg = new;
}

static char	*substitute_each(char *arg)
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
