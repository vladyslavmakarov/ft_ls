/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 16:20:13 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 01:38:32 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		recurse(const char *path, t_flags *flags, int counter, int m)
{
	t_tree	*directory_content;
	char	**subdirectories;
	int		i;

	i = -1;
	put_header_recurse(path, flags, counter, m);
	if (test_access((char *)path) == 0)
	{
		directory_content = get_directory_content(path, flags);
		subdirectories = get_subdirectories(directory_content, path, flags);
		main_display(directory_content, flags);
		delete_tree(directory_content);
		while (subdirectories[++i])
		{
			if (counter == 0 && m == 0 && ft_strcmp(path, ".") != 0 &&
														flags->rcrs != 0)
				ft_putstr("\n");
			flags->rcrs++;
			counter = recurse(subdirectories[i], flags, counter, m);
			free(subdirectories[i]);
		}
	}
	else if (test_access((char *)path) == 10)
		deal_denial((char *)path);
	return (counter += 1);
}

void	put_header_recurse(const char *path, t_flags *flags, int counter, int m)
{
	if (ft_strcmp(path, ".") != 0 && flags->rcrs != 0)
		ft_putstr("\n");
	if (((counter != 0 || ((counter == 0 && ft_strcmp(path, ".") != 0)))
		&& m != 1) || flags->rcrs != 0)
	{
		if (((ft_strncmp(path, "././", 4) != -47 && flags->rcrs == 0) || m == 0)
			&& flags->rcrs != 0)
		{
			ft_putstr(path);
			ft_putstr(":\n");
		}
		else
			recurse_put_path(path);
	}
}

char	**get_subdirectories(t_tree *directory_content,
									const char *path, t_flags *flags)
{
	int		size;
	char	**array;

	size = get_size_of_array(path, 0, flags);
	if (!(array = (char **)malloc(sizeof(char **) * (size + 1))))
		return (NULL);
	if (flags->r != '\0')
		fill_array_r(directory_content, array, 0, flags);
	else
		fill_array(directory_content, array, 0, flags);
	array[size] = NULL;
	return (array);
}

int		get_size_of_array(const char *path, int counter, t_flags *flags)
{
	DIR				*directory;
	struct dirent	*dir_pointer;
	char			*file_path;
	struct stat		s;

	directory = opendir(path);
	if (!directory)
		return (0);
	while ((dir_pointer = readdir(directory)) != NULL)
	{
		file_path = ft_strjoin(path, "/");
		file_path = ft_strjoin(file_path, dir_pointer->d_name);
		if (stat(file_path, &s) == 0)
		{
			if ((s.st_mode & S_IFDIR) && (ft_strncmp(dir_pointer->d_name,
	".", 1) != 0) && flags->a == '\0' && (ft_strcmp(dir_pointer->d_name,
	".") != 0 && ft_strcmp(dir_pointer->d_name, "..") != 0))
				counter++;
			if ((s.st_mode & S_IFDIR) && flags->a != '\0' && (ft_strcmp
(dir_pointer->d_name, ".") != 0 && ft_strcmp(dir_pointer->d_name, "..") != 0))
				counter++;
		}
	}
	closedir(directory);
	return (counter);
}
