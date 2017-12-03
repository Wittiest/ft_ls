/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:54:38 by dpearson          #+#    #+#             */
/*   Updated: 2017/11/30 09:54:39 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_dir(char *path)
{
	struct stat stats;

	if (lstat(path, &stats) == -1)
		return (print_error(path));
	return (S_ISDIR(stats.st_mode));
}

char	*str_join_delim(const char *s1, char *s2, char *delim)
{
	char	*merge;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(delim) + 1;
	merge = ft_strnew(len);
	if (merge)
	{
		ft_strcpy(merge, s1);
		ft_strcat(merge, delim);
		ft_strcat(merge, s2);
	}
	return (merge);
}

/*
**	bitwise & checks for the bits 0000000100001001 in sta.st_mode for
**	S_IRUSR(256) , so 16877 for example would be valid. Only the same
**	bits are copied over. There are set combinations for the permissions
**	to allow all representations.
*/

void	get_permissions(struct stat sta)
{
	if (S_ISLNK(sta.st_mode))
		ft_putchar('l');
	else
		ft_putchar(((S_ISDIR(sta.st_mode)) ? 'd' : '-'));
	ft_putchar((sta.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((sta.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((sta.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((sta.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((sta.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((sta.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((sta.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((sta.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((sta.st_mode & S_IXOTH) ? 'x' : '-');
	ft_putstr("  ");
}

char	*readlink_malloc(const char *filename)
{
	int		size;
	int		ret;
	char	*buffer;

	buffer = NULL;
	size = 10;
	while (1)
	{
		buffer = ft_realloc(buffer, size);
		ret = readlink(filename, buffer, size);
		if (ret < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (ret < size)
			return (buffer);
		size *= 2;
	}
}

void	print_l(t_tree *head)
{
	struct stat stats;
	char		*time;
	char		*sym;
	int			ret;

	if (lstat(head->path, &stats) != -1)
	{
		time = ft_strsub(ctime(&stats.st_mtimespec.tv_sec), 4, 12);
		get_permissions(stats);
		ft_putnbr(stats.st_nlink);
		putstr_spaces(1, getpwuid(stats.st_uid)->pw_name, 2);
		putstr_spaces(0, getgrgid(stats.st_gid)->gr_name, 1);
		ret = ft_putllnbr(stats.st_size);
		putstr_spaces(20 - ret, time, 2);
		ft_putstr(head->name);
		free(time);
		if ((S_ISLNK(stats.st_mode)) && (sym = readlink_malloc(head->path)))
		{
			ft_putstr(" -> ");
			ft_putstr(sym);
			free(sym);
		}
	}
	else
		print_error(head->path);
}
