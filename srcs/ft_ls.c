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

static void		handle_children(t_tree *head, t_flags *flags, int colon)
{
	DIR		*dirstream;
	t_tree	*iter;

	if (flags->bigr)
	{
		iter = head;
		while ((head = iter))
		{
			iter = head->next;
			if ((dirstream = open_dir(head->path, colon)))
			{
				if (head->next)
					ft_putchar('\n');
				down(dirstream, head, flags, 1);
				break ;
			}
			free_node(head);
		}
	}
	else
		free_items(head);
}

static void		handle_next(t_tree *branch, t_flags *flags, int colon)
{
	DIR		*dirstream;
	t_tree	*store;
	t_tree	*iter;

	store = branch;
	iter = branch->next;
	while ((branch = iter))
	{
		iter = branch->next;
		if ((dirstream = open_dir((branch)->path, colon)))
		{
			ft_putchar('\n');
			down(dirstream, branch, flags, 1);
			break ;
		}
		free_node(branch);
	}
	free_node(store);
}

void			down(DIR *dirstream, t_tree *branch, t_flags *flags, int colon)
{
	t_tree				**head;
	struct dirent		*file;
	char				*tmppath;
	long long			i;

	i = 0;
	if (colon || branch->next)
		print_path(branch->path);
	head = ft_memalloc(sizeof(t_tree *));
	while ((file = readdir(dirstream)))
	{
		if ((!(flags->a)) && file->d_name[0] == '.')
			continue ;
		tmppath = str_join_delim(branch->path, file->d_name, "/");
		i += get_size(tmppath);
		tree_handler(head, flags, file->d_name, tmppath);
		free(tmppath);
	}
	closedir(dirstream);
	print_side(*head, branch->next != NULL, flags, i);
	handle_children(*head, flags, colon);
	handle_next(branch, flags, colon);
	free(head);
}

static void		parse_args2(t_tree **item_head, t_tree **tree_head,
							int blocksize, t_flags *flags)
{
	DIR			*dirstream;
	int			colon;

	if (*item_head)
	{
		print_side(*item_head, *tree_head != NULL, flags, blocksize);
		free_items(*item_head);
	}
	colon = *item_head != NULL;
	if (*tree_head)
	{
		while (!(dirstream = open_dir((*tree_head)->path, colon)))
		{
			colon = 1;
			*tree_head = (*tree_head)->next;
			if (!(*tree_head))
				break ;
		}
		if (*tree_head)
			down(dirstream, *tree_head, flags, colon);
	}
	free(item_head);
	free(tree_head);
}

void			parse_args(t_flags *flags, int argc, char **argv, int i)
{
	t_tree		**item_head;
	t_tree		**tree_head;
	int			ret;
	int			blocksize;

	tree_head = ft_memalloc(sizeof(t_tree *));
	item_head = ft_memalloc(sizeof(t_tree *));
	blocksize = 0;
	if (argc == 0)
		tree_handler(tree_head, flags, ".", ".");
	while (++i < argc)
	{
		if (((ret = is_dir(argv[i])) == -1))
			continue ;
		if (ret)
			tree_handler(tree_head, flags, argv[i], argv[i]);
		else
		{
			blocksize += (get_size(argv[i]));
			tree_handler(item_head, flags, argv[i], ".");
		}
	}
	parse_args2(item_head, tree_head, blocksize, flags);
}
