/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 03:52:23 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/08 03:52:24 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "../libs/libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <uuid/uuid.h>

typedef struct	s_flags
{
	int l;
	int a;
	int R;
	int	r;
	int	t;
}				t_flags;

/*
**	A lexicographically sorted list of the data we will print for each item
**	or directory.
*/
typedef struct			s_list_lex
{
	char				*sort_name;
	char				*print_data;
	struct s_list_lex	*next;
}						t_list_lex;

/*
**	Holds the head of LL of items and head of LL of directories. The items get
**	printed first. This will become a linked list when I create the -R flag.
*/
// typedef	struct	s_dir_item
// {
// 	t_list_lex	*item_head;
// 	// t_list_lex	*dir_head;
// }				t_dir_item;

void	lst_add_lex(t_list_lex **head, t_list_lex *node);

#endif
