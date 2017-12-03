/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:56:00 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/02 17:56:00 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long long	get_size(char *path)
{
	struct stat stats;

	if (lstat(path, &stats) != -1)
		return (stats.st_blocks);
	else
		print_error(path);
	return (0);
}

DIR			*open_dir(char *path, int colon)
{
	DIR				*dirstream;

	if (is_dir(path))
	{
		if (!(dirstream = opendir(path)))
		{
			if (colon)
				print_path(path);
			print_error(path);
			return (NULL);
		}
		return (dirstream);
	}
	return (NULL);
}
