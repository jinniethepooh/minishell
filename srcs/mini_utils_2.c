#include "minishell.h"

static int quotes_checker(t_shell *sh)
{
	int	i;
	int	curr_q;

	i = 0;
	curr_q = 0;
	while (sh->from_rl[i] && !ft_isquotes(sh->from_rl[i]))
		++i;
	while (sh->from_rl[i])
	{
		if (ft_isquotes(sh->from_rl[i]))
		{
			curr_q = sh->from_rl[i++];
			i += ft_loop_until(&sh->from_rl[i], curr_q, 0);
		}
		if (sh->from_rl[i] == curr_q)
			curr_q = 0;
		++i;
	}
	return (curr_q);
}

static int	ft_isvalid_quotes(t_shell *sh)
{
	if (quotes_checker(sh))
	{
		printf("tinyshell: "RED"invaid quotes\n");
		sh->exit_status = EXIT_FAILURE;
		return (0);
	}
	return (1);
}

static int	ft_isvalid_pipe(t_shell *sh)
{
	char	**temp;
	int		i;

	if (sh->from_rl[ft_strlen(sh->from_rl) - 1] == '|')
	{
		put_error(NULL, "|", 2);
		return (0);
	}
	temp = ft_split(sh->from_rl, '|');
	i = 0;
	while (temp[i])
	{
		if (ft_isspace_str(temp[i++]))
		{
			put_error(NULL, "|", 2);
			free_2d(temp);
			return (0);
		}
	}
	free_2d(temp);
	return (1);
}

static int	ft_isvalid_redir(t_shell *sh)
{
	return (1);
}

int	is_input_valid(t_shell *sh)
{
	if (ft_isvalid_quotes(sh) && ft_isvalid_pipe(sh))
	{
		if (ft_isvalid_redir(sh))
			return (1);
	}
	return (0);
}
