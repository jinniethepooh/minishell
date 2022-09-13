/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:00:14 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 12:00:22 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*exp_stack_new(char *name, char *val)
{
	t_export	*node;

	node = malloc(sizeof(*node));
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

void	exp_stack_remove_if(t_export **head, char *data_ref)
{
	t_export	*cur;

	if (!(head && *head))
		return ;
	cur = *head;
	if (ft_strcmp(cur->name, data_ref) == 0)
	{
		*head = cur->prev;
		if (cur->name)
			free(cur->name);
		if (cur->val)
			free(cur->val);
		free(cur);
		exp_stack_remove_if(head, data_ref);
	}
	exp_stack_remove_if(&cur->prev, data_ref);
}
