/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_init_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 02:39:52 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 02:39:55 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags	*get_flags(char **av)
{
	t_flags	*options;
	int		i;
	int		j;

	options = init_flag();
	i = 1;
	while (av[i])
	{
		j = 1;
		if (av[i][0] != '-')
			return (options);
		while (av[i][j])
		{
			options = set_flag(av[i][j], options);
			j++;
		}
		i++;
	}
	return (options);
}

t_flags	*set_flag(char c, t_flags *options)
{
	if (c == 'l')
		options->l = 'l';
	else if (c == 'a')
		options->a = 'a';
	else if (c == 't')
		options->t = 't';
	else if (c == 'R')
		options->r_b = 'R';
	else if (c == 'r')
		options->r = 'r';
	else if (c == 'G')
		options->g_b = 'G';
	else if (c == 's')
		options->s = 's';
	else if (c == 'S')
		options->s_b = 'S';
	else if (c == 'i')
		options->i = 'i';
	else if (c == 'o')
		options->o = 'o';
	else
		show_usage_and_exit(c, options);
	return (options);
}

void	show_usage_and_exit(char c, t_flags *options)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\nusage: ls [-GRSailorst] [file ...]\n");
	deinit_flag(options);
	exit(1);
}
