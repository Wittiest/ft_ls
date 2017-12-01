/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 01:08:09 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/28 01:08:10 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	item_handler(t_tree **child_list_head, t_flags *flags, char *name)
{
	t_tree	*item;

	item = ft_memalloc(sizeof(t_tree));
	item->name = ft_strdup(name);
	add_tree_node(child_list_head, item, flags);
}

int		dir_children_handler(t_tree **child_head, t_flags *flags, DIR *dirstream, char *path)
{
	struct dirent	*file;
	char			*tmp;
	int				is_children;
	t_tree			*store;

	is_children = 0;
	while ((file = readdir(dirstream)))
	{
		if ((!(flags->a)) && file->d_name[0] == '.')
			continue ;
		if (!is_children)
			is_children = 1;
		item_handler(child_head, flags, file->d_name);
	}
	store = *(child_head);
	while ((*child_head))
	{
		tmp = str_join_delim(path, (*child_head)->name, "/");
		if (flags->R && is_dir(tmp))
		{
			(*child_head)->is_dir = 1;
			(*child_head)->path = tmp;
		}
		else
			free(tmp);
		(*child_head) = (*child_head)->next;
	}
	*child_head = store;
	return (is_children);
}

void	sub_dir_handler(t_tree **child_head, t_flags *flags)
{
	DIR				*dirstream;
	t_tree			*store;

	store = (*child_head);
	while (*child_head)
	{
		if ((*child_head)->is_dir)
		{
			(*child_head)->child_list = ft_memalloc(sizeof(t_tree *));
			*((*child_head)->child_list) = NULL;
			if (!(dirstream = opendir((*child_head)->path)))
			{
				printf("ls: %s: %s\n", (*child_head)->path, strerror(errno));
				(*child_head) = (*child_head)->next;
				continue ;
			}
			if (dir_children_handler((*child_head)->child_list, flags, dirstream, (*child_head)->path))
				(*child_head)->is_dir = 1;
			else
				(*child_head)->is_dir = 0;
			closedir(dirstream);
			sub_dir_handler((*child_head)->child_list, flags);
		}
		(*child_head) = (*child_head)->next;
	}
	(*child_head) = store;
}

void	top_dir_handler(t_tree **tree_head, t_flags *flags, char *path)
{
	DIR				*dirstream;
	t_tree			*branch;

	branch = ft_memalloc(sizeof(t_tree));
	branch->name = ft_strdup(path);
	branch->path = ft_strdup(path);
	branch->child_list = ft_memalloc(sizeof(t_tree *));
	*(branch->child_list) = NULL;
	if (!(dirstream = opendir(path)))
	{
		printf("ls: %s: %s\n", path, strerror(errno));
		return ;
	}
	add_tree_node(tree_head, branch, flags);	
	if (dir_children_handler(branch->child_list, flags, dirstream, path))
		branch->is_dir = 1;
	else
		branch->is_dir = 0;
	closedir(dirstream);
	sub_dir_handler(branch->child_list, flags);
}

void	parse_args(t_flags *flags, int argc, int i, char **argv)
{
	t_tree		**tree_head;
	t_tree		**item_head;

	tree_head = ft_memalloc(sizeof(t_tree *));
	item_head = ft_memalloc(sizeof(t_tree *));
	if (i >= argc)
		top_dir_handler(tree_head, flags, ".");
	while (i < argc)
	{
		if (is_dir(argv[i]))
			top_dir_handler(tree_head, flags, argv[i]);
		else
			item_handler(item_head, flags, argv[i]);
		i++;
	}
	if (*item_head)
		print_tree(*item_head);
	if (*tree_head)
		print_tree(*((*tree_head)->child_list));
}