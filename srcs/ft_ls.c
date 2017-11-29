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
		printf("usage: ls [-Ralrt] [file ...]");
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
		printf("ls: %s: %s\n", path, strerror(errno));
		exit(errno);
	}
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}


void	dir_handler(t_list_lex **dirhead, char *path, t_flags *flags)
{
	// handle flags
		//exclude hidden files unless -a	
	// write simple case of printing first
	// recursivity handled later
	DIR				*dir;
	// struct dirent	*file;
	t_list_lex		*dir_item;
	dir_item = (t_list_lex *)(malloc(sizeof(t_list_lex)));
	flags = NULL; //SILENCE
	if (!(dir = opendir(path)))
	{
		printf("ls: %s: %s\n", path, strerror(errno)); // these errors need to be printed in order, use an error buff
		return ;
	}
	dir_item->sort_name = path;
	dir_item->print_data = path;
	dir_item->next = NULL;
	lst_add_lex(dirhead, dir_item);
	// while ((file = readdir(dir)))
	// 	list_file_data(file->d_name);
	closedir(dir);
}

void	item_handler(t_list_lex **itemhead, char *path, t_flags *flags)
{
	// handle flags
			//exclude hidden files unless -a
	// write case of simple print first
	// never care about recursivity
	t_list_lex *item;
	struct stat stats;

	flags = NULL; //SILENCE
	item = (t_list_lex *)(malloc(sizeof(t_list_lex)));
	if (stat(path, &stats) == -1)
	{
		printf("ls: %s: %s\n", path, strerror(errno));// these errors need to be printed in order, use an error buff
		exit(errno);
	}
	item->sort_name = path;
	item->print_data = path;
	item->next = NULL;
	lst_add_lex(itemhead, item);
}

void	print_lex(t_list_lex *head)
{
	while (head)
	{
		printf("%s\n", head->print_data);
		head = head->next;
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
	t_list_lex **item_head;// list of items from initial paths
	t_list_lex **dir_head; // list of directories from initial paths

	item_head = (t_list_lex **)malloc(sizeof(t_list_lex *));
	dir_head = (t_list_lex **)malloc(sizeof(t_list_lex *));
	(*item_head) = NULL;
	(*dir_head) = NULL;
	if (i >= argc)
		printf("NO ARGS == ls -[-Ralrt] . (current directory) \n");
	while (i < argc)
	{
		path = argv[i];
		is_dir(path) ? dir_handler(dir_head, path, flags) : item_handler(item_head, path, flags);
		i++;
	}
	print_lex(*item_head);
	print_lex(*dir_head);  // if printing more than one directory, dirname: files
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
