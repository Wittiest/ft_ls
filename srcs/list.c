/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 04:07:54 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/29 04:07:55 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
/*
**	Function will insert given node to a list pointed to by head, placing the
**	node in its lexicographic position.
*/

void	lst_add_lex(t_list_lex **head, t_list_lex *node)
{
	t_list_lex *before;
	t_list_lex *store;

	if (!(*head))
		(*head) = node;
	else
	{
		store = (*head);
		before = (*head);
		while (*head)
		{
			if (ft_strcmp(node->sort_name, (*head)->sort_name) <= 0)
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
