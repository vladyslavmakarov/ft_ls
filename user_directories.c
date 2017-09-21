/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_directories.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 03:35:35 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 03:35:36 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		**get_directories(char **av, t_flags *flags)
{
	int		size;
	int		i;
	char	**result;
	t_tree	*directories;
	char	*path;

	directories = NULL;
	size = n_of_dirs(av);
	i = -1;
	if (size == 0)
		return (NULL);
	if (!(result = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (av[++i])
	{
		path = p(av[i]);
		if (is_dir(path) != 0)
			add_data_main(&directories, path, av[i], flags);
	}
	if (flags->r != '\0')
		dir_inputs_r(directories, result, 0);
	else
		dir_inputs(directories, result, 0);
	result[size] = NULL;
	return (result);
}

int			n_of_dirs(char **av)
{
	int		result;
	int		i;
	char	*path;

	i = 0;
	result = 0;
	while (av[i])
	{
		if (av[i])
			path = p(av[i]);
		if (is_dir(path) != 0)
			result++;
		i++;
	}
	return (result);
}

int			dir_inputs_r(t_tree *directory_content, char **array, int i)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->right != NULL)
		i = dir_inputs_r(directory_content->right, array, i);
	array[i++] = ft_strdup(directory_content->path);
	if (directory_content->left != NULL)
		i = dir_inputs_r(directory_content->left, array, i);
	return (i);
}

int			dir_inputs(t_tree *directory_content, char **array, int i)
{
	if (directory_content == NULL)
		return (0);
	if (directory_content->left != NULL)
		i = dir_inputs(directory_content->left, array, i);
	array[i++] = ft_strdup(directory_content->path);
	if (directory_content->right != NULL)
		i = dir_inputs(directory_content->right, array, i);
	return (i);
}
