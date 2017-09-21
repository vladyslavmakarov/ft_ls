/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 01:37:57 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 01:37:58 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		fill_array(t_tree *directory_content, char **array,
										int i, t_flags *flags)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->left != NULL)
		i = fill_array(directory_content->left, array, i, flags);
	if ((is_dir(directory_content->path) != 0) && flags->a == '\0' &&
				(ft_strncmp(directory_content->info->name, ".", 1) != 0))
		array[i++] = (char *)directory_content->path;
	if ((is_dir(directory_content->path) != 0) && flags->a != '\0' &&
					(ft_strcmp(directory_content->info->name, ".") != 0 &&
					ft_strcmp(directory_content->info->name, "..") != 0))
		array[i++] = (char *)directory_content->path;
	if (directory_content->right != NULL)
		i = fill_array(directory_content->right, array, i, flags);
	return (i);
}

int		fill_array_r(t_tree *directory_content, char **array, int i,
														t_flags *flags)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->right != NULL)
		i = fill_array_r(directory_content->right, array, i, flags);
	if ((is_dir(directory_content->path) != 0) && flags->a == '\0' &&
				(ft_strncmp(directory_content->info->name, ".", 1) != 0))
		array[i++] = (char *)directory_content->path;
	if ((is_dir(directory_content->path) != 0) && flags->a != '\0' &&
					(ft_strcmp(directory_content->info->name, ".") != 0 &&
					ft_strcmp(directory_content->info->name, "..") != 0))
		array[i++] = (char *)directory_content->path;
	if (directory_content->left != NULL)
		i = fill_array_r(directory_content->left, array, i, flags);
	return (i);
}

void	recurse_put_path(const char *path)
{
	if (path[0] == '/')
		ft_putstr(path);
	else
		ft_putstr_from(path, 2);
	ft_putstr(":\n");
}
