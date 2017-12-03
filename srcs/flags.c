/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:53:17 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/30 09:53:17 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	flag_check(char c, t_flags *flags)
{
	if (c == 'l')
		flags->l = 1;
	else if (c == 'a')
		flags->a = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'R')
		flags->bigr = 1;
	else if (c == 't')
		flags->t = 1;
	else
	{
		ft_putstr("ls: illegal option -- ");
		ft_putchar(c);
		ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
		exit(1);
	}
}

int		parse_flags(t_flags *flags, int argc, char **argv)
{
	int i;
	int j;

	if (argc < 2)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (i);
		j = 1;
		while (argv[i][j])
		{
			flag_check(argv[i][j], flags);
			j++;
		}
		i++;
	}
	return (i);
}
