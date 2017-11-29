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

void	lst_add_item(t_item **head, t_item *node, t_flags *flags)
{
	t_item *before;
	t_item *store;
	int cmp;

	if (!(*head))
		(*head) = node;
	else
	{
		store = (*head);
		before = (*head);
		while (*head)
		{
			cmp = ft_strcmp(node->sort_name, (*head)->sort_name) >= 0;
			if (((flags->r && cmp) || ((!flags->r) && !cmp)))
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

void	lst_add_dir(t_dir **head, t_dir *node, t_flags *flags)
{
	t_dir *before;
	t_dir *store;
	int cmp;

	if (!(*head))
		(*head) = node;
	else
	{
		store = (*head);
		before = (*head);
		while (*head)
		{
			cmp = ft_strcmp(node->dir_name, (*head)->dir_name) >= 0;
			if (((flags->r && cmp) || ((!flags->r) && !cmp)))
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