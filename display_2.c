/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 23:18:49 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/24 23:18:52 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		is_empty_dir(t_tree *directory_content, int i)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->left != NULL)
		i = is_empty_dir(directory_content->left, i);
	if (ft_strcmp(directory_content->info->name, ".") != 0 &&
		ft_strcmp(directory_content->info->name, "..") != 0)
		i++;
	if (directory_content->right != NULL)
		i = is_empty_dir(directory_content->right, i);
	return (i);
}

int		calculate_s(t_tree *directory_content, int total, t_flags *flags)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->left != NULL)
		total = calculate_s(directory_content->left, total, flags);
	if (flags->a != '\0')
		total = total + directory_content->info->s;
	if (flags->a == '\0' && ft_strncmp(directory_content->info->name,
														".", 1) != 0)
		total = total + directory_content->info->s;
	if (directory_content->right != NULL)
		total = calculate_s(directory_content->right, total, flags);
	return (total);
}

int		is_symlink(char const *s)
{
	char	result[256];
	int		len;

	len = readlink(s, result, sizeof(result));
	if (len == -1)
		return (0);
	else
		return (1);
}

void	put_symlink(char const *s)
{
	char	result[256];
	int		len;

	len = readlink(s, result, sizeof(result));
	if (len == -1)
		return ;
	else
	{
		ft_putstr(" -> ");
		result[len] = '\0';
		ft_putstr(result);
	}
}
