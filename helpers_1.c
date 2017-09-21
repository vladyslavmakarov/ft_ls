/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 03:47:56 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 17:44:52 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_putstr_from(const char *src, int i)
{
	int j;

	j = 0;
	while (src[j])
	{
		if (j >= i)
			ft_putchar(src[j]);
		j++;
	}
}

int		is_dir(const char *path)
{
	struct stat s;

	if (stat(path, &s) != 0)
		return (0);
	return (S_ISDIR(s.st_mode));
}

void	ft_ls_helper_1(t_inputs *inputs_non_existant, t_flags *flags,
												t_tree *inputs_files)
{
	if (inputs_non_existant)
		display_errors(inputs_non_existant);
	if (inputs_files)
		display_inputs(inputs_files, flags);
}

void	ft_ls_helper_2(char *s)
{
	if (s[0] == '/')
		ft_putstr(s);
	else
		ft_putstr_from(s, 2);
	ft_putstr(":\n");
}
