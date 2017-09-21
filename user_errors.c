/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 03:34:09 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 03:34:12 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_inputs	*get_errors(char **av)
{
	int			i;
	struct stat	st;
	char		*path;
	t_inputs	*result;
	int			flag;

	i = 1;
	result = NULL;
	flag = 0;
	while (av[i])
	{
		path = p(av[i]);
		if (av[i][0] == '-' && flag == 0 && av[i][1] != '\0')
			i++;
		else if (stat(path, &st) == 0)
		{
			flag = 1;
			i++;
		}
		else if (stat(path, &st) != 0)
			add_data_inputs(&result, av[i++], &ft_strcmp);
		else
			i++;
	}
	return (result);
}

char		*p(char *s)
{
	char *res;

	res = NULL;
	if (s[0] != '/')
		res = ft_strjoin("./", s);
	else if (s[0] == '/')
		res = s;
	return (res);
}

void		display_errors(t_inputs *errors)
{
	if (errors->left)
		display_errors(errors->left);
	ft_putstr("ls: ");
	ft_putstr(errors->name);
	ft_putstr(": No such file or directory\n");
	if (errors->right)
		display_errors(errors->right);
}

int			test_access(char *path)
{
	DIR *d;

	d = opendir(path);
	if (d != NULL)
	{
		closedir(d);
		return (0);
	}
	if (errno == EACCES)
		return (10);
	return (-1);
}
