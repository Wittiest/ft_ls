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
	int flag_l;
	int flag_a;
	int flag_R:
	int	flag_r;
	int	flag_t;
}				t_flags;

/*
**	A lexicographically sorted list of the data we will print for each item
**	or directory.
*/
typedef struct			s_list_lex
{
	char				*sort_name;
	char				*print_data;
	struct s_list_hex	*next;
}						t_list;

/*
**	Holds the head of LL of items and head of LL of directories. The items get
**	printed first.
*/
typedef	struct	s_dir_item
{
	t_list	*item_head;
	t_list	*dir_head;
}				t_dir_item;

#endif
