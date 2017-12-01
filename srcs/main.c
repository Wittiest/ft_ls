/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:59:17 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/30 09:59:17 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_flags		*flags;
	int			i;

	flags = ft_memalloc(sizeof(t_flags)); 
	flags->a = 0;
	flags->l = 0;
	flags->r = 0;
	flags->t = 0;
	flags->R = 0;
	i = parse_flags(flags, argc, argv);
	parse_args(flags, argc - i, argv + i);
	free(flags);
	return (0);
}