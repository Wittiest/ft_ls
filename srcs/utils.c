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
	{
		printf("ls: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
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
		printf("l");
	else
		printf((S_ISDIR(sta.st_mode)) ? "d" : "-");
	printf((sta.st_mode & S_IRUSR) ? "r" : "-");
	printf((sta.st_mode & S_IWUSR) ? "w" : "-");
	printf((sta.st_mode & S_IXUSR) ? "x" : "-");
	printf((sta.st_mode & S_IRGRP) ? "r" : "-");
	printf((sta.st_mode & S_IWGRP) ? "w" : "-");
	printf((sta.st_mode & S_IXGRP) ? "x" : "-");
	printf((sta.st_mode & S_IROTH) ? "r" : "-");
	printf((sta.st_mode & S_IWOTH) ? "w" : "-");
	printf((sta.st_mode & S_IXOTH) ? "x" : "-");
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

	if (lstat(head->path, &stats) == -1)
	{
		printf("\nls: %s: %s\n", head->path, strerror(errno));
		return ;
	}
	time = ft_strsub(ctime(&stats.st_mtimespec.tv_sec), 4, 12);
	get_permissions(stats);
	printf("  ");
	printf("%d  ", stats.st_nlink);
	printf("%s %s ", getpwuid(stats.st_uid)->pw_name,
			getgrgid(stats.st_gid)->gr_name);
	printf("%*lld ", 6, stats.st_size); // MAKE FUNCTION TO PRINT CORRECTLY
	printf("%s %s", time, head->name);
	if ((S_ISLNK(stats.st_mode)))
		if ((sym = readlink_malloc(head->path)))
		{
			printf(" -> %s", sym);
			free(sym);
		}
	printf("\n");
}
