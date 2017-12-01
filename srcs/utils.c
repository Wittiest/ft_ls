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
		printf("ls: %s %s\n", path, strerror(errno));
		return (0);
	}
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

/*
**	Merge s2 to the back of s1 with delimiter delim, auto-nullbyte
*/
char	*str_join_delim(char *s1, char *s2, char *delim)
{

	char	*merge;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(delim) + 1;
	merge = ft_memalloc(sizeof(char) * len);
	if (merge)
	{
		ft_strcpy(merge, s1);
		ft_strcat(merge, delim);
		ft_strcat(merge, s2);	
	}
	return (merge);
}