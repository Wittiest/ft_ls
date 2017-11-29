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


/*
**	Currently done with if statements, later create an enum and jump table.
**	the -g flag overrides the -l flag regardless of order.
**	possible need for precendence function, or just check for g or l in logic,
**	checking for g first
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
	else if (c == 't')
		flags->t = 1;
	else
	{
		printf("ls: illegal option -- %c\nusage: ls [-Ralrt] [file ...]\n", c);
		exit(1);
	}
}

int		parse_flags(t_flags *flags, int argc, char **argv)
{
	int i;
	int j;

	if (argc < 2)
		return (1); // only doing ls for current directory. No flags
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
**	Uses macro S_ISDIR to identify as directory or !directory
*/
int		is_dir(char *path)
{
	struct stat stats;

	if (stat(path, &stats) == -1)
	{
		printf("ls: %s %s\n", path, strerror(errno));
		exit(errno);
	}
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

void	add_item(t_item **itemhead, char *path, t_flags *flags)
{
	t_item *item;

	item = (t_item *)(malloc(sizeof(t_item)));
	item->sort_name = path;
	item->print_data = path;
	item->next = NULL;
	lst_add_item(itemhead, item, flags);
}

void	item_handler(t_item **itemhead, char *path, t_flags *flags)
{
	// handle flags
	//exclude hidden files unless -a
	// never care about recursivity
	struct stat stats;

	if (stat(path, &stats) == -1)
	{
		printf("ls: %s: %s\n", path, strerror(errno));// these errors need to be printed in order, use an error buff
		exit(errno);
	}
	add_item(itemhead, path, flags);
}

void	dir_handler(t_dir **dirhead, char *path, t_flags *flags)
{
	// handle flags
		//exclude hidden files unless -a	
	// write simple case of printing first
	// recursivity handled later
	DIR				*dirstream;
	struct dirent	*file;
	t_dir			*dir;

	dir = (t_dir *)(malloc(sizeof(t_dir)));
	if (!(dirstream = opendir(path)))
	{
		printf("ls: %s: %s\n", path, strerror(errno));
		return ;
	}
	dir->dir_name = path;
	dir->item_head = (t_item **)malloc(sizeof(t_item *));
	*(dir->item_head) = NULL;
	dir->next = NULL;
	while ((file = readdir(dirstream)))
	{
		if ((!(flags->a)) && file->d_name[0] == '.')
			continue ;
		add_item(dir->item_head, file->d_name, flags);
	}
	lst_add_dir(dirhead, dir, flags);
	closedir(dirstream);
}

void	print_items(t_item *head)
{
	while (head)
	{
		printf("%s\n", head->sort_name);
		head = head->next;
	}
}
void	print_dir(t_dir *head, int alreadyprinted)
{
	if (alreadyprinted)
		printf("\n");
	if (head->next)
		alreadyprinted = 1;
	while (head)
	{
		if (alreadyprinted)
			printf("%s:\n", head->dir_name);
		while (*(head->item_head))
		{
			printf("%s ", (*(head->item_head))->print_data);
			*(head->item_head) = (*(head->item_head))->next;
			if (head)
				printf("\n");
		}
		head = head->next;
		if (head)
			printf("\n");
	}
}
/*
**	parse_args is given the end of the argument vector to iterate through.
**	It will identify the directories and files listed after the ls flags,
**	first displaying the non-directorys lexicographically, then the same with
**	the directories.
*/
void	parse_args(t_flags *flags, int argc, int i, char **argv)
{
	char *path;
	t_item **item_head;// list of items from initial paths
	t_dir **dir_head; // list of directories from initial paths
	int alreadyprinted;

	alreadyprinted = 0;
	item_head = (t_item **)malloc(sizeof(t_item *));
	dir_head = (t_dir **)malloc(sizeof(t_item *));
	(*item_head) = NULL;
	(*dir_head) = NULL;
	if (i >= argc)
		dir_handler(dir_head, ".", flags);
	while (i < argc)
	{
		path = argv[i];
		is_dir(path) ? dir_handler(dir_head, path, flags) : item_handler(item_head, path, flags);
		i++;
	}
	if (*item_head)
	{
		alreadyprinted = 1;
		print_items(*item_head);
	}
	if (*dir_head)
		print_dir(*dir_head, alreadyprinted);  // if printing more than one directory, dirname: files
}

/*
	If the modification time of the file is more than 6 months in the past or future, then the year
	of the last modification is displayed in place of the hour and minute fields.
*/
int		main(int argc, char **argv)
{
	t_flags		flags;
	int			i;

	i = parse_flags(&flags, argc, argv);
	parse_args(&flags, argc, i, argv);
	return (0);
}



//FOR REFERENCE:
// void	list_file_data(char *filename)
// {
// 	struct stat stats;
// 	char 		*time;
// 	if (filename[0] != '.')
// 	{
// 		printf("test filename: %s\n", filename);
// 		if (stat(filename, &stats) == -1)
// 		{
// 			printf("\nls: %s: %s\n", filename, strerror(errno));
// 			return ;
// 		}
// 		time = ft_strsub(ctime(&stats.st_mtimespec.tv_sec), 4, 12);
// 		printf("%d %s %s %lld %s %s\n",stats.st_nlink, getpwuid(stats.st_uid)->pw_name,
// 			getgrgid(stats.st_gid)->gr_name, stats.st_size, time, filename);
// 	}
// }

// void	list_files(const char *filename)
// {
// 	DIR				*dir;
// 	struct dirent	*file;

// 	if (!(dir = opendir(filename)))
// 	{
// 		printf("ls: %s: %s\n", filename, strerror(errno));
// 		exit(errno);
// 	}
// 	while ((file = readdir(dir)))
// 		list_file_data(file->d_name);
// }
