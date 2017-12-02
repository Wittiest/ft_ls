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

int		sort_node(t_tree *node, t_tree *comp, t_flags *flags)
{
	struct stat stats;
	struct stat statscomp;

	if (flags->t)
	{
		if (lstat(node->path, &stats) == -1)
		{
			printf("ls: %s: %s\n", node->path, strerror(errno));
			return (-1);
		}
		if (lstat(comp->path, &statscomp) == -1)
		{
			printf("ls: %s: %s\n", node->path, strerror(errno));
			return (-1);
		}
		if (stats.st_mtimespec.tv_sec > statscomp.st_mtimespec.tv_sec)
			return (!flags->r);
		if (stats.st_mtimespec.tv_sec < statscomp.st_mtimespec.tv_sec)
			return (flags->r);
		if (stats.st_mtimespec.tv_nsec > statscomp.st_mtimespec.tv_nsec)
			return (!flags->r);
		if (stats.st_mtimespec.tv_nsec < statscomp.st_mtimespec.tv_nsec)
			return (flags->r);
	}
	return ((ft_strcmp(node->name, comp->name) >= 0 ? flags->r : !flags->r));
}

/*
**	Adds node to tree sorted. Returns 1 when the head was manipulated and needs
**	to be reset.
*/

int		add_tree_node(t_tree **head, t_tree *node, t_flags *flags)
{
	t_tree *before;

	before = (*head);
	while (*head)
	{
		if (sort_node(node, (*head), flags))
		{
			if (*head == before)
			{
				node->next = (*head);
				(*head) = node;
				return (0);
			}
			else
			{
				node->next = (*head);
				break ;
			}
		}
		before = (*head);
		(*head) = (*head)->next;
	}
	before->next = node;
	return (1);
}

void	tree_handler(t_tree **head, t_flags *flags, char *name, char *path)
{
	t_tree	*item;
	t_tree	*store;

	item = ft_memalloc(sizeof(t_tree));
	item->name = ft_strdup(name);
	item->path = ft_strdup(path);
	item->next = NULL;
	if (!*head)
		*head = item;
	else
	{
		store = (*head);
		if (add_tree_node(head, item, flags))
			(*head) = store;
	}
}
