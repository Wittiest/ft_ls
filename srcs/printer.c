/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 10:00:57 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/30 10:00:58 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//recursive print
void	print_tree(t_tree *head)
{
	t_tree	*store;
	int		hit;
	int		hit2;

	hit = 0;
	store = head;
	while (head)
	{
		hit2 = 1;
		printf("%s\n", head->name);
		head = head->next;
	}
	while (store)
	{
		if (store->is_dir)
		{
			if (store->next || hit | hit2)
			{
				if (hit || hit2)
					printf("\n");
				printf("%s: \n", store->path);
			}
			hit = 1;
			print_tree(*(store->child_list));
		}
		store = store->next;
	}
}