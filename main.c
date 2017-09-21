/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 16:16:01 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 17:42:13 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			main(int ac, char **av)
{
	t_inputs	*inputs_non_existant;
	t_flags		*flags;
	t_tree		*inputs_files;
	char		**inputs_dirs;

	flags = check_flag(get_flags(av));
	inputs_non_existant = get_errors(av);
	inputs_files = get_files(av, flags);
	inputs_dirs = get_directories(av, flags);
	if (inputs_dirs)
		ac = size_of_2d_array(inputs_dirs);
	if (!inputs_non_existant && !inputs_files && (!inputs_dirs || (ac == 1
		&& (ft_strcmp(inputs_dirs[0], "./.") == 0))))
	{
		kostyl(flags);
		return (0);
	}
	if (flags->r_b == '\0')
		ft_ls(inputs_non_existant, flags, inputs_files, inputs_dirs);
	else if (flags->r_b != '\0')
		ft_ls_r(inputs_non_existant, flags, inputs_files, inputs_dirs);
	clean_vars(inputs_non_existant, flags, inputs_files, inputs_dirs);
	return (0);
}

void		ft_ls(t_inputs *inputs_non_existant, t_flags *flags,
						t_tree *inputs_files, char **inputs_dirs)
{
	int i;
	int len;

	i = -1;
	ft_ls_helper_1(inputs_non_existant, flags, inputs_files);
	if (inputs_dirs)
	{
		len = size_of_2d_array(inputs_dirs);
		while (inputs_dirs[++i])
		{
			if (inputs_files && i == 0)
				ft_putstr("\n");
			if (len > 1 || inputs_non_existant || inputs_files)
				ft_ls_helper_2(inputs_dirs[i]);
			if (test_access(inputs_dirs[i]) == 0)
			{
				inputs_files = get_directory_content(inputs_dirs[i], flags);
				main_display(inputs_files, flags);
			}
			if (test_access(inputs_dirs[i]) == 10)
				deal_denial(inputs_dirs[i]);
			if (inputs_dirs[i + 1] != NULL)
				ft_putstr("\n");
		}
	}
}

void		ft_ls_r(t_inputs *inputs_non_existant, t_flags *flags,
	t_tree *inputs_files, char **inputs_dirs)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	ft_ls_helper_1(inputs_non_existant, flags, inputs_files);
	if (inputs_files)
		flags->rcrs = 1;
	if (inputs_dirs)
	{
		if (inputs_files && i != 0 && len != 0 && flags->rcrs == 0)
			ft_putstr("\n");
		while (inputs_dirs[len])
			len++;
		while (inputs_dirs[i])
		{
			recurse(inputs_dirs[i], flags, 0, len);
			i++;
			flags->rcrs = 1;
		}
	}
}

t_tree		*get_files(char **av, t_flags *flags)
{
	t_tree		*result;
	int			i;
	struct stat st;
	char		*path;

	i = 1;
	result = NULL;
	while (av[i])
	{
		path = p(av[i]);
		if (stat(path, &st) == 0 && is_dir(path) == 0)
			add_data_main(&result, path, av[i], flags);
		i++;
	}
	return (result);
}

t_tree		*get_directory_content(const char *path, t_flags *flags)
{
	DIR				*directory;
	struct dirent	*dir_pointer;
	t_tree			*directory_content;
	char			*file_path;

	directory_content = NULL;
	directory = opendir(path);
	if (directory)
	{
		while ((dir_pointer = readdir(directory)) != NULL)
		{
			file_path = ft_strjoin(path, "/");
			file_path = ft_strjoin(file_path, dir_pointer->d_name);
			add_data_main(&directory_content, file_path,
										dir_pointer->d_name, flags);
		}
	}
	closedir(directory);
	return (directory_content);
}
