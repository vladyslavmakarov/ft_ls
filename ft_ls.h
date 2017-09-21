/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <vmakarov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 13:32:29 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/17 14:03:35 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "./libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct		s_info
{
	int				s;
	int				i;
	char			type;
	char			owner_perm1;
	char			owner_perm2;
	char			owner_perm3;
	char			group_perm1;
	char			group_perm2;
	char			group_perm3;
	char			other_perm1;
	char			other_perm2;
	char			other_perm3;
	int				n_of_hlinks;
	char			*owner;
	char			*group;
	int				size;
	char			*time_modif;
	char			*name;
	int				time_mod_sec;
	int				time_mod_nsec;

}					t_info;

typedef	struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	const char		*path;
	t_info			*info;
}					t_tree;

typedef	struct		s_flags
{
	char			l;
	char			a;
	char			t;
	char			r_b;
	char			r;
	char			g_b;
	char			s;
	char			s_b;
	char			i;
	char			o;
	int				rcrs;
}					t_flags;

typedef struct		s_inputs
{
	struct s_inputs	*left;
	struct s_inputs	*right;
	const char		*name;
}					t_inputs;

/*
**		BTREE_HELPERS_1.C
*/

t_tree				*create_tree(const char *path, t_info *info);
t_tree				*init_tree(void);
void				delete_tree(t_tree *root);

/*
**		BTREE_HELPERS_2.C
*/

void				add_data_main(t_tree **root, const char *path, char *name,
																t_flags *fl);
void				add_data_alpha(t_tree **root, const char *path, t_info *new,
							int (*cmpf) (const char *, const char *));
void				add_data_size(t_tree **root, const char *path, t_info *new);
void				add_data_time(t_tree **root, const char *path, t_info *new);

/*
**		DIR_INFO_1.C
*/

t_info				*init_info(void);
void				deinit_info(t_info *root);
void				print_info(t_info *root);
void				put_permissions(t_info *root);
t_info				*zero_perm(t_info *root);

/*
**		DIR_INFO_2.C
*/

t_info				*get_dir_info(const char *path, char *name);
t_info				*get_permissions(struct stat st, t_info *result);
t_info				*get_setuid(struct stat st, t_info *result);
t_info				*get_setgid(struct stat st, t_info *result);
t_info				*get_sticky_bit(struct stat st, t_info *result);

/*
**		DISPLAY_1.C
*/

void				main_display(t_tree *directory_content,
														t_flags *flags);
void				display_directory_content(t_tree *directory_content,
														t_flags *flags);
void				display_directory_content_r(t_tree *directory_content,
														t_flags *flags);
void				display_directory_content_a(t_tree *directory_content,
														t_flags *flags);
void				display_directory_content_ar(t_tree *directory_content,
														t_flags *flags);
void				display_inputs(t_tree *directory_content,
															t_flags *flags);
/*
**		DISPLAY_2.C
*/

int					is_empty_dir(t_tree *directory_content, int i);
int					calculate_s(t_tree *directory_content, int total,
														t_flags *flags);
int					is_symlink(char const *s);
void				put_symlink(char const *s);

/*
**		DISPLAY_3.C
*/

void				display_name (t_tree *directory_content, t_flags *flags);
void				display_long(t_tree *directory_content, t_flags *flags);
void				display_perm(t_tree *directory_content);
void				display_helper(t_tree *directory_content, t_flags *flags);
void				clean_vars(t_inputs *a, t_flags *b, t_tree *c, char **d);

/*
**		HELPERS_1.C
*/

int					is_dir(const char *path);
void				ft_putstr_from(const char *src, int i);
void				ft_ls_helper_1(t_inputs *inputs_non_existant, t_flags
							*flags, t_tree *inputs_files);
void				ft_ls_helper_2(char *s);

/*
**		HELPERS_2.C
*/

int					size_of_2d_array(char **array);
void				kostyl(t_flags *flags);
void				deal_denial(char *path);

/*
**		MAIN.C
*/

t_tree				*get_files(char **av, t_flags *flags);
t_tree				*get_directory_content(const char *path, t_flags *flags);
void				ft_ls(t_inputs *inputs_non_existant, t_flags *flags,
						t_tree	*inputs_files, char **inputs_dirs);
void				ft_ls_r(t_inputs *inputs_non_existant, t_flags *flags,
						t_tree	*inputs_files, char **inputs_dirs);

/*
**		OPTIONS_INIT_1.C
*/

t_flags				*init_flag();
void				deinit_flag(t_flags *root);
void				print_flags(t_flags *list);
t_flags				*check_flag(t_flags *flag);

/*
**		OPTIONS_INIT_2.C
*/

t_flags				*get_flags(char **av);
t_flags				*set_flag(char c, t_flags *options);
void				show_usage_and_exit(char c, t_flags *options);

/*
**		RECURSION_1.C
*/

int					recurse(const char *path, t_flags *flags, int counter,
															int m);
char				**get_subdirectories(t_tree *directory_content,
										const char *path, t_flags *flags);
int					get_size_of_array(const char *path, int counter,
														t_flags *flags);
void				put_header_recurse(const char *path, t_flags *flags,
													int counter, int m);

/*
**		RECURSION_2.C
*/

int					fill_array(t_tree *directory_content, char **array,
													int i, t_flags *flags);
int					fill_array_r(t_tree *directory_content, char **array,
													int i, t_flags *flags);
void				recurse_put_path(const char *path);

/*
**		USER_DIRECTORIES.C
*/

char				**get_directories(char **av, t_flags *flags);
int					n_of_dirs(char **av);
int					dir_inputs_r(t_tree *directory_content, char **array,
																		int i);
int					dir_inputs(t_tree *directory_content, char **array, int i);
char				*p(char *s);

/*
**		USER_ERRORS.C
*/

t_inputs			*get_errors(char **av);
void				display_errors(t_inputs *errors);
int					test_access(char *path);
char				*p(char *s);

/*
**		USER_INPUTS.C
*/

t_inputs			*create_tree_inputs(const char *name);
t_inputs			*init_tree_inputs();
void				deinit_tree_inputs(t_inputs *root);
void				delete_tree_inputs(t_inputs *root);
void				add_data_inputs(t_inputs **root, const char *name, int
									(*cmpf) (const char *, const char *));

#endif
