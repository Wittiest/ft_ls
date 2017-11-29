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
typedef struct			s_item
{
	char				*sort_name;
	char				*print_data;
	struct s_item	*next;
}						t_item;

/*
**	Holds the head of LL of items and head of LL of directories. The items get
**	printed first. This will become a linked list when I create the -R flag.
*/
typedef	struct	s_dir
{
	char		*dir_name;
	t_item	**item_head;
	struct s_dir *next;
}				t_dir;

void	lst_add_item(t_item **head, t_item *node, t_flags *flags);
void	lst_add_dir(t_dir **head, t_dir *node, t_flags *flags);

#endif
