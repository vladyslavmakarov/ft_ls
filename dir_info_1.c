/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_info_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 19:39:45 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 02:09:49 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info	*init_info(void)
{
	t_info *new;

	new = (t_info *)malloc(sizeof(t_info));
	new->s = 0;
	new->i = 0;
	new = zero_perm(new);
	new->n_of_hlinks = 0;
	new->owner = NULL;
	new->group = NULL;
	new->size = 0;
	new->time_modif = NULL;
	new->name = NULL;
	new->time_mod_sec = 0;
	new->time_mod_nsec = 0;
	return (new);
}

void	deinit_info(t_info *root)
{
	if (root != 0)
	{
		root->s = 0;
		root->i = 0;
		root = zero_perm(root);
		root->n_of_hlinks = 0;
		if (root->owner)
			free(root->owner);
		if (root->group)
			free(root->group);
		root->size = 0;
		if (root->time_modif)
			free(root->time_modif);
		if (root->name)
			free(root->name);
		root->time_mod_sec = 0;
		root->time_mod_nsec = 0;
		free(root);
	}
}

t_info	*zero_perm(t_info *root)
{
	root->type = '-';
	root->owner_perm1 = '-';
	root->owner_perm2 = '-';
	root->owner_perm3 = '-';
	root->group_perm1 = '-';
	root->group_perm2 = '-';
	root->group_perm3 = '-';
	root->other_perm1 = '-';
	root->other_perm2 = '-';
	root->other_perm3 = '-';
	return (root);
}

void	print_info(t_info *root)
{
	if (root != 0)
	{
		ft_putnbr(root->i);
		ft_putstr("  ");
		ft_putnbr(root->s);
		ft_putstr("  ");
		put_permissions(root);
		ft_putstr("  ");
		ft_putnbr(root->n_of_hlinks);
		ft_putstr(" ");
		ft_putstr(root->owner);
		ft_putstr("  ");
		ft_putstr(root->group);
		ft_putstr("  ");
		ft_putnbr(root->size);
		ft_putstr("  ");
		ft_putstr(root->time_modif);
		ft_putstr("  ");
		ft_putstr(root->name);
	}
}

void	put_permissions(t_info *root)
{
	if (root != 0)
	{
		ft_putchar(root->type);
		ft_putchar(root->owner_perm1);
		ft_putchar(root->owner_perm2);
		ft_putchar(root->owner_perm3);
		ft_putchar(root->group_perm1);
		ft_putchar(root->group_perm2);
		ft_putchar(root->group_perm3);
		ft_putchar(root->other_perm1);
		ft_putchar(root->other_perm2);
		ft_putchar(root->other_perm3);
	}
}
