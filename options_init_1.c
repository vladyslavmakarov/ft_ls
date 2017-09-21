/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_init_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 15:52:44 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 02:39:31 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags	*init_flag(void)
{
	t_flags *new;

	new = (t_flags *)malloc(sizeof(t_flags));
	new->l = '\0';
	new->a = '\0';
	new->t = '\0';
	new->r_b = '\0';
	new->r = '\0';
	new->g_b = '\0';
	new->s = '\0';
	new->s_b = '\0';
	new->i = '\0';
	new->o = '\0';
	new->rcrs = 0;
	return (new);
}

void	deinit_flag(t_flags *root)
{
	if (root != 0)
	{
		root->l = '\0';
		root->a = '\0';
		root->t = '\0';
		root->r_b = '\0';
		root->r = '\0';
		root->g_b = '\0';
		root->s = '\0';
		root->s_b = '\0';
		root->i = '\0';
		root->o = '\0';
		root->rcrs = 0;
		free(root);
	}
}

void	print_flags(t_flags *list)
{
	ft_putstr("The list is as follows:"RED);
	if (!list)
		return ;
	if (list->l != '\0')
		ft_putchar(list->l);
	if (list->a != '\0')
		ft_putchar(list->a);
	if (list->t != '\0')
		ft_putchar(list->t);
	if (list->r_b != '\0')
		ft_putchar(list->r_b);
	if (list->r != '\0')
		ft_putchar(list->r);
	if (list->g_b != '\0')
		ft_putchar(list->g_b);
	if (list->s != '\0')
		ft_putchar(list->s);
	if (list->s_b != '\0')
		ft_putchar(list->s_b);
	if (list->i != '\0')
		ft_putchar(list->i);
	if (list->o != '\0')
		ft_putchar(list->o);
	ft_putstr(RESET"\n");
}

t_flags	*check_flag(t_flags *flag)
{
	if (flag->s_b != '\0' && flag->t != '\0')
		flag->t = '\0';
	return (flag);
}
