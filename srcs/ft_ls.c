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

void	print_side(t_tree *head, int new)
{
	t_tree	*save;

	save = head;
	while (head)
	{
		printf("%s\n", head->name);
		head = head->next;
	}
	if (new)
		printf("\n");
	head = save;
}

DIR		*open_dir(char *path)
{
	DIR				*dirstream;	
	if (is_dir(path))
	{
		if (!(dirstream = opendir(path)))
		{
			printf("\n%s:\n", path);
			printf("ls: %s: %s\n", path, strerror(errno));
			return (NULL);
		}
		return (dirstream);
	}
	return (NULL);
}

void	handle_next(t_tree *branch, t_flags *flags)
{
	t_tree	*i;
	DIR		*dirstream;

	i = branch->first_kid;
	if (flags->R)
	{
		while (i)
		{
			if ((dirstream = open_dir(i->path)))
			{
				if (i->first_kid || i->next || (!(branch->next)))
					printf("\n");
				down(dirstream, i, flags, 1);
				break;
			}
			i = i->next;		
		}
	}
	while ((branch = branch->next))
		if ((dirstream = open_dir((branch)->path)))
		{
			down(dirstream, branch, flags, 1);
			break;
		}
}

void	down(DIR* dirstream, t_tree *branch, t_flags *flags, int colon)
{
	t_tree			**head;
	struct dirent	*file;
	char			*tmppath;

	if (colon || branch->next)
		printf("%s:\n", branch->path);
	head = ft_memalloc(sizeof(t_tree *));
	while ((file = readdir(dirstream)))
	{
		if ((!(flags->a)) && file->d_name[0] == '.')
			continue ;
		tmppath = str_join_delim(branch->path, file->d_name, "/");
		tree_handler(head, flags, file->d_name, tmppath);
		free(tmppath);
	}
	closedir(dirstream);
	branch->first_kid = *(head);
	print_side(*head, branch->next != NULL);
	handle_next(branch, flags);
}

void	parse_args(t_flags *flags, int argc, char **argv)
{
	t_tree		**item_head;
	t_tree		**tree_head;
	DIR			*dirstream;
	int			i;
	int			ret;

	tree_head = ft_memalloc(sizeof(t_tree *));
	item_head = ft_memalloc(sizeof(t_tree *));
	i = 0;
	if (argc == 0)
		tree_handler(tree_head, flags, ".", ".");
	while (i < argc)
	{
		if (((ret = is_dir(argv[i])) != -1))
		{
			if (ret)
				tree_handler(tree_head, flags, argv[i], argv[i]);
			else
				tree_handler(item_head, flags, argv[i], ".");
		}
		i++;
	}
	if (*item_head)
		print_side(*item_head, *tree_head != NULL);
	if (*tree_head)
		if ((dirstream = open_dir((*tree_head)->path)))
			down(dirstream, *tree_head, flags, *item_head != NULL);
}
