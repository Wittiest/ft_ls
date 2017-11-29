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

/*
**	Function will insert given node to a list pointed to by head, placing the
**	node in its lexicographic position. It will allocate the data for the node.
*/

void	lst_add_lex(t_list *head, t_list node)
{
	//	allocate memory for node.
	//	Iterate through list with head until (str_cmp(node->sort_name, head->sort_name) < 0)
	//	Set (head - 1)->next to node
	//	Set (node)->next to current head.
	//	Node has been inserted at correct position and allocated.
}
