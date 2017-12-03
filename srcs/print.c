/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:35:16 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/02 16:35:16 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	512 is block size
*/

void		print_side(t_tree *head, int new, t_flags *flags, long long s)
{
	t_tree *store;

	store = head;
	if (flags->l)
	{
		ft_putstr("total ");
		ft_putllnbr(s);
		ft_putchar('\n');
	}
	while (head)
	{
		if (flags->l)
			print_l(head);
		else
			ft_putstr(head->name);
		ft_putchar('\n');
		head = head->next;
	}
	if (new)
		ft_putchar('\n');
	head = store;
}

void		putstr_spaces(int i, char *str, int n)
{
	while (i--)
		ft_putchar(' ');
	ft_putstr(str);
	while (n--)
		ft_putchar(' ');
}

void		print_path(char *path)
{
	ft_putstr(path);
	ft_putstr(":\n");
}

int			print_error(char *path)
{
	ft_putstr("ls: ");
	perror(path);
	return (-1);
}

int			ft_putllnbr(long long n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		i += ft_putllnbr(n / 10);
		i += ft_putllnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
		i++;
	}
	return (i);
}
