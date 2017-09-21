/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 11:42:10 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/20 11:42:15 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_inputs	*create_tree_inputs(const char *name)
{
	t_inputs *new;

	new = (t_inputs *)malloc(sizeof(t_inputs));
	new->left = NULL;
	new->right = NULL;
	new->name = ft_strdup(name);
	return (new);
}

t_inputs	*init_tree_inputs(void)
{
	t_inputs *new;

	new = (t_inputs *)malloc(sizeof(t_inputs));
	new->left = NULL;
	new->right = NULL;
	new->name = NULL;
	return (new);
}

void		deinit_tree_inputs(t_inputs *root)
{
	if (root != 0)
	{
		root->left = NULL;
		root->right = NULL;
		free((void *)root->name);
		free(root);
	}
}

void		delete_tree_inputs(t_inputs *root)
{
	if (root != 0)
	{
		delete_tree_inputs(root->left);
		delete_tree_inputs(root->right);
		free((void *)root->name);
		free(root);
	}
}

void		add_data_inputs(t_inputs **root, const char *name,
							int (*cmpf) (const char *, const char *))
{
	t_inputs *fork;

	if (!*root)
	{
		*root = create_tree_inputs(name);
		return ;
	}
	fork = *root;
	if ((*cmpf)(name, fork->name) <= 0)
	{
		if (fork->left)
			add_data_inputs(&fork->left, name, cmpf);
		else
			fork->left = create_tree_inputs(name);
	}
	else
	{
		if (fork->right)
			add_data_inputs(&fork->right, name, cmpf);
		else
			fork->right = create_tree_inputs(name);
	}
}
