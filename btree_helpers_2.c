/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_helpers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 23:51:14 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/24 23:51:15 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_data_main(t_tree **root, const char *path, char *name, t_flags *fl)
{
	t_info	*info;

	info = get_dir_info(path, name);
	if (fl->t != '\0')
		add_data_time(*&root, path, info);
	else if (fl->s_b != '\0')
		add_data_size(*&root, path, info);
	else
		add_data_alpha(*&root, path, info, &ft_strcmp);
}

void	add_data_alpha(t_tree **root, const char *path, t_info *new,
									int (*cmpf) (const char *, const char *))
{
	t_tree	*fork;

	if (!*root)
	{
		*root = create_tree(path, new);
		return ;
	}
	fork = *root;
	if ((*cmpf)(new->name, fork->info->name) < 0)
	{
		if (fork->left)
			add_data_alpha(&fork->left, path, new, cmpf);
		else
			fork->left = create_tree(path, new);
	}
	else
	{
		if (fork->right)
			add_data_alpha(&fork->right, path, new, cmpf);
		else
			fork->right = create_tree(path, new);
	}
}

void	add_data_size(t_tree **root, const char *path, t_info *new)
{
	t_tree	*fork;

	if (!*root)
	{
		*root = create_tree(path, new);
		return ;
	}
	fork = *root;
	if (new->size > fork->info->size || (new->size == fork->info->size
							&& ft_strcmp(new->name, fork->info->name) < 0))
	{
		if (fork->left)
			add_data_size(&fork->left, path, new);
		else
			fork->left = create_tree(path, new);
	}
	else
	{
		if (fork->right)
			add_data_size(&fork->right, path, new);
		else
			fork->right = create_tree(path, new);
	}
}

void	add_data_time(t_tree **root, const char *path, t_info *new)
{
	t_tree	*fork;

	if (!*root)
	{
		*root = create_tree(path, new);
		return ;
	}
	fork = *root;
	if ((new->time_mod_sec > fork->info->time_mod_sec) || ((new->time_mod_sec ==
fork->info->time_mod_sec) && (new->time_mod_nsec > fork->info-> time_mod_nsec)
) || (((new->time_mod_sec == fork->info->time_mod_sec) && (new->time_mod_nsec ==
fork->info->time_mod_nsec)) && (ft_strcmp(new->name, fork->info->name) < 0)))
	{
		if (fork->left)
			add_data_time(&fork->left, path, new);
		else
			fork->left = create_tree(path, new);
	}
	else
	{
		if (fork->right)
			add_data_time(&fork->right, path, new);
		else
			fork->right = create_tree(path, new);
	}
}
