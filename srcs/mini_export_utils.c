#include "minishell.h"

t_export	*exp_stack_new(char *name, char *val)
{
	t_export	*node;

	node = malloc(sizeof(*node));
	node->status = 1;
	node->name = name;
	node->val = val;
	node->prev = NULL;
	return (node);
}

void	exp_stack_push(t_export **stack, t_export *node)
{
	if (!stack)
		return ;
	node->prev = *stack;
	*stack = node;
}

void	exp_stack_clear(t_export **head)
{
	t_export	*cur;

	if (!(head && *head))
		return ;
	cur = *head;
	*head = cur->prev;
	if (cur->name)
		free(cur->name);
	if (cur->val)
		free(cur->val);
	free(cur);
	exp_stack_clear(head);
}

int	is_export_bef(char *name)
{
	t_export	*exp;
	int			ret;

	ret = 0;
	exp = g_var.export;
	while (exp)
	{
		if (ft_strcmp(exp->name, name) == 0)
		{
			if (exp->status < 0)
			{
				exp->status = 0;
				ret = 1;
			}
		}
		exp = exp->prev;
	}
	return (ret);
}
