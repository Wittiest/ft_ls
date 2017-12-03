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

#ifndef FT_LS_H
# define FT_LS_H

# include "../libs/libft/includes/libft.h"
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <uuid/uuid.h>

typedef struct		s_flags
{
	int				l;
	int				a;
	int				bigr;
	int				r;
	int				t;
}					t_flags;

typedef struct		s_tree
{
	char			*name;
	char			*path;
	struct s_tree	*next;
}					t_tree;

void				flag_check(char c, t_flags *flags);
int					parse_flags(t_flags *flags, int argc, char **argv);
int					is_dir(char *path);
void				parse_args(t_flags *flags, int argc, char **argv, int i);
int					add_tree_node(t_tree **head, t_tree *node, t_flags *flags);
char				*str_join_delim(const char *s1, char *s2, char *delim);
void				down(DIR *dirstream, t_tree *branch, t_flags *flags,
					int colon);
void				tree_handler(t_tree **head, t_flags *flags, char *name,
					char *path);
void				print_l(t_tree *head);
void				free_items(t_tree *head);
void				free_node(t_tree *node);
void				print_path(char *path);
int					print_error(char *path);
long long			get_size(char *path);
void				print_side(t_tree *head, int new, t_flags *flags,
					long long s);
DIR					*open_dir(char *path, int colon);
int					ft_putllnbr(long long n);
void				putstr_spaces(int i, char *str, int n);
#endif
