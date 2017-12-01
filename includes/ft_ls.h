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

typedef struct		s_tree
{
	int				is_dir;
	char			*name;
	char			*path;
	char			*print_statement;
	struct s_tree	*next;
	struct s_tree	**child_list; // double pointer so that head can be moved
}					t_tree;

void	flag_check(char c, t_flags *flags);
int		parse_flags(t_flags *flags, int argc, char **argv);
int		is_dir(char *path);
void	parse_args(t_flags *flags, int argc, int i, char **argv);
void	add_tree_node(t_tree **head, t_tree *node, t_flags *flags);
void	print_tree(t_tree *head);
char	*str_join_delim(char *s1, char *s2, char *delim);

#endif
