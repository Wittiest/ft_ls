/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 04:07:54 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/29 04:07:55 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_lex_node(t_tree *node, t_tree *comp, t_flags *flags)
{
	int cmp;

	cmp = ft_strcmp(node->name, comp->name) >=0;
	return((flags->r && cmp) || ((!flags->r) && !cmp));
}

void	add_tree_node(t_tree **head, t_tree *node, t_flags *flags)
{
	t_tree *before;
	t_tree *store;
	if (!(*head))
		(*head) = node;
	else
	{
		store = (*head);
		before = (*head);
		while (*head)
		{
			if (sort_lex_node(node, (*head), flags))
			{
				if ((*head) == before)
				{
					node->next = before;
					(*head) = node;
				}
				else
				{
					node->next = before->next;
					before->next = node;
					(*head) = store;
				}
				return ;
			}
			before = (*head);
			(*head) = (*head)->next;
		}
		before->next = node;
		(*head) = store;
	}
}