/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_helpers_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 14:02:58 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/24 23:51:35 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_tree	*create_tree(const char *path, t_info *info)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->left = NULL;
	new->right = NULL;
	new->path = ft_strdup(path);
	new->info = info;
	return (new);
}

t_tree	*init_tree(void)
{
	t_tree *new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->left = NULL;
	new->right = NULL;
	new->path = NULL;
	new->info = NULL;
	return (new);
}

void	delete_tree(t_tree *root)
{
	if (root != 0)
	{
		delete_tree(root->left);
		delete_tree(root->right);
		free(root);
	}
}
