/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 01:08:09 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/28 01:08:10 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	list_file_data(char *filename)
{
	struct stat stats;
	char 		*time;
	if (filename[0] != '.')
	{
		if (stat(filename, &stats) == -1)
		{
			printf("ls: %s: %s\n", filename, strerror(errno));
			return ;
		}
		time = ft_strsub(ctime(&stats.st_mtimespec.tv_sec), 4, 12);
		printf("%d %s %s %lld %s %s\n",stats.st_nlink, getpwuid(stats.st_uid)->pw_name,
			getgrgid(stats.st_gid)->gr_name, stats.st_size, time, filename);
	}
}

void	list_files(const char *filename)
{
	DIR				*dir;
	struct dirent	*file;
	if (!(dir = opendir(filename)))
	{
		printf("ls: %s: %s\n", filename, strerror(errno));
		exit(errno);
	}
	while ((file = readdir(dir)))
		list_file_data(file->d_name);
}

int		main(int argc, char **argv)
{
	// parsing with usage statement
	// flags -l (multiple column format), -R, -a , -r, -t
	// flag -l always overrides -g
	if (argc == 1)
		list_files(".");
	if (argc == 2)
		list_files(argv[1]);
	return (0);
}