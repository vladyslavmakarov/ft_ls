/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 16:19:13 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/18 16:20:17 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	main_display(t_tree *directory_content, t_flags *flags)
{
	int total_s;

	total_s = calculate_s(directory_content, 0, flags);
	if ((flags->l != '\0' || flags->o != '\0') &&
		(is_empty_dir(directory_content, 0) != 0 || flags->a != '\0'))
	{
		ft_putstr("total ");
		ft_putnbr(total_s);
		ft_putstr("\n");
	}
	if (flags->a == '\0' && flags->r == '\0')
		display_directory_content(directory_content, flags);
	else if (flags->a == '\0' && flags->r != '\0')
		display_directory_content_r(directory_content, flags);
	else if (flags->a != '\0' && flags->r == '\0')
		display_directory_content_a(directory_content, flags);
	else if (flags->a != '\0' && flags->r != '\0')
		display_directory_content_ar(directory_content, flags);
}

void	display_directory_content(t_tree *directory_content,
													t_flags *flags)
{
	if (directory_content->left)
		display_directory_content(directory_content->left, flags);
	if (ft_strncmp(directory_content->info->name, ".", 1) != 0)
		display_helper(directory_content, flags);
	if (directory_content->right)
		display_directory_content(directory_content->right, flags);
}

void	display_directory_content_r(t_tree *directory_content,
														t_flags *flags)
{
	if (directory_content->right)
		display_directory_content_r(directory_content->right, flags);
	if (ft_strncmp(directory_content->info->name, ".", 1) != 0)
		display_helper(directory_content, flags);
	if (directory_content->left)
		display_directory_content_r(directory_content->left, flags);
}

void	display_directory_content_a(t_tree *directory_content,
														t_flags *flags)
{
	if (directory_content->left)
		display_directory_content_a(directory_content->left, flags);
	display_helper(directory_content, flags);
	if (directory_content->right)
		display_directory_content_a(directory_content->right, flags);
}

void	display_directory_content_ar(t_tree *directory_content,
														t_flags *flags)
{
	if (directory_content->right)
		display_directory_content_ar(directory_content->right, flags);
	display_helper(directory_content, flags);
	if (directory_content->left)
		display_directory_content_ar(directory_content->left, flags);
}
