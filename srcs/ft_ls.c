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
/*
**	Currently done with if statements, later create an enum and jump table.
**	the -g flag overrides the -l flag regardless of order.
*/
void	flag_check(char c, t_flags *flags)
{
	if (c == 'l')
		flags->l = 1;
	else if (c == 'a')
		flags->a = 1;
	else if (c == 'r')
		flags->r = 1;
	else if (c == 'R')
		flags->R = 1;
	else if (c == t)
		flags->t = 1;
}

int		parse_flags(t_flags *flags, int argc, char **argv)
{
	int i;
	int j;

	if (argc < 2)
		return ;
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

/*	I need a function that can store all of the data in a directory, using a LL
**	It will iterate through the LL, comparing the directory/filename and placing
**	its arg lexicographically.
*/

/*
**	parse_args is given the end of the argument vector to iterate through.
**	It will identify the directories and files listed after the ls flags,
**	first displaying the non-directorys lexicographically, then the same with
**	the directories.
*/
void	parse_args(t_flags *flags, int argc, int i, char **argv)
{
	if (i >= argc)
		printf("CASE OF NO ARGUMENTS == PRINT . DIRECTORY FILES with flags\n")
	while (i < argc)
	{
		list_files(argv[i]);
		i++;
	}
}

/*
	If the modification time of the file is more than 6 months in the past or future, then the year
	of the last modification is displayed in place of the hour and minute fields.
*/
int		main(int argc, char **argv)
{
	t_flags		flags;
	int			i;

	i = parse_flags(&flags, argc, argv)
	parse_args(&flags, argc, i, argv);
	return (0);
}
