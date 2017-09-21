/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 22:17:35 by vmakarov          #+#    #+#             */
/*   Updated: 2017/09/04 22:17:38 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		size_of_2d_array(char **array)
{
	int result;

	result = 0;
	while (array[result])
		result++;
	return (result);
}

void	kostyl(t_flags *flags)
{
	t_tree		*directory_content;

	directory_content = get_directory_content("./", flags);
	if (flags->r_b == '\0')
		main_display(directory_content, flags);
	else
		recurse(".", flags, 0, 0);
	delete_tree(directory_content);
}

void	deal_denial(char *path)
{
	char	**s;

	s = ft_strsplit(path, '/');
	ft_putstr("ls: ");
	ft_putstr(s[size_of_2d_array(s) - 1]);
	ft_putstr(": Permission denied\n");
	free(s);
}

void	clean_vars(t_inputs *a, t_flags *b, t_tree *c, char **d)
{
	free(a);
	deinit_flag(b);
	free(c);
	free(d);
}
