/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 01:12:15 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 17:47:53 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_inputs(t_tree *directory_content, t_flags *flags)
{
	if (flags->a == '\0' && flags->r == '\0')
		display_directory_content(directory_content, flags);
	else if (flags->a == '\0' && flags->r != '\0')
		display_directory_content_r(directory_content, flags);
	else if (flags->a != '\0' && flags->r == '\0')
		display_directory_content_a(directory_content, flags);
	else if (flags->a != '\0' && flags->r != '\0')
		display_directory_content_ar(directory_content, flags);
	else
		return ;
}

void	display_name(t_tree *directory_content, t_flags *flags)
{
	if (flags->g_b != '\0' && directory_content->info->other_perm3
			== 'x' && directory_content->info->type != 'd')
		ft_putstr(RED);
	if (flags->g_b != '\0' && is_dir(directory_content->path) != 0)
		ft_putstr(BLUE);
	if (flags->g_b != '\0' && is_symlink(directory_content->path) != 0)
		ft_putstr(GREEN);
	ft_putstr(directory_content->info->name);
	free(directory_content->info->name);
	ft_putstr(RESET);
}

void	display_long(t_tree *directory_content, t_flags *flags)
{
	ft_putchar(directory_content->info->type);
	display_perm(directory_content);
	ft_putstr("  ");
	ft_putnbr(directory_content->info->n_of_hlinks);
	ft_putchar(' ');
	ft_putstr(directory_content->info->owner);
	ft_putstr("  ");
	if (flags->o == '\0')
		ft_putstr(directory_content->info->group);
	ft_putstr("  ");
	ft_putnbr(directory_content->info->size);
	ft_putstr(" ");
	ft_putstr(directory_content->info->time_modif);
	ft_putstr(" ");
	if (flags->g_b != '\0' && directory_content->info->other_perm3 == 'x')
		ft_putstr(RED);
	if (flags->g_b != '\0' && is_dir(directory_content->path) != 0)
		ft_putstr(BLUE);
	if (flags->g_b != '\0' && is_symlink(directory_content->path) != 0)
		ft_putstr(GREEN);
	ft_putstr(directory_content->info->name);
	ft_putstr(RESET);
	put_symlink(directory_content->path);
}

void	display_perm(t_tree *directory_content)
{
	ft_putchar(directory_content->info->owner_perm1);
	ft_putchar(directory_content->info->owner_perm2);
	ft_putchar(directory_content->info->owner_perm3);
	ft_putchar(directory_content->info->group_perm1);
	ft_putchar(directory_content->info->group_perm2);
	ft_putchar(directory_content->info->group_perm3);
	ft_putchar(directory_content->info->other_perm1);
	ft_putchar(directory_content->info->other_perm2);
	ft_putchar(directory_content->info->other_perm3);
}

void	display_helper(t_tree *directory_content, t_flags *flags)
{
	if (flags->i != '\0')
	{
		ft_putnbr(directory_content->info->i);
		ft_putstr(" ");
	}
	if (flags->s != '\0')
	{
		ft_putnbr(directory_content->info->s);
		ft_putstr(" ");
	}
	if (flags->l != '\0' || flags->o != '\0')
		display_long(directory_content, flags);
	else
		display_name(directory_content, flags);
	ft_putstr("\n");
}
