/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_info_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmakarov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 02:10:18 by vmakarov          #+#    #+#             */
/*   Updated: 2017/08/25 02:10:20 by vmakarov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*get_dir_info(const char *path, char *name)
{
	t_info			*result;
	struct stat		st;
	struct passwd	*user;
	struct group	*grp;

	lstat(path, &st);
	result = init_info();
	result->s = st.st_blocks;
	result->i = st.st_ino;
	if (S_ISDIR(st.st_mode))
		result->type = 'd';
	if (S_ISLNK(st.st_mode))
		result->type = 'l';
	result = get_permissions(st, result);
	result->n_of_hlinks = st.st_nlink;
	if ((user = getpwuid(st.st_uid)) != NULL)
		result->owner = user->pw_name;
	if ((grp = getgrgid(st.st_gid)) != NULL)
		result->group = grp->gr_name;
	result->size = st.st_size;
	result->time_modif = ft_strsub(ctime(&st.st_mtime), 4, 12);
	result->name = ft_strdup(name);
	result->time_mod_sec = st.st_mtimespec.tv_sec;
	result->time_mod_nsec = st.st_mtimespec.tv_nsec;
	return (result);
}

t_info		*get_permissions(struct stat st, t_info *result)
{
	if (st.st_mode & S_IRUSR)
		result->owner_perm1 = 'r';
	if (st.st_mode & S_IWUSR)
		result->owner_perm2 = 'w';
	result = get_setuid(st, result);
	if (st.st_mode & S_IRGRP)
		result->group_perm1 = 'r';
	if (st.st_mode & S_IWGRP)
		result->group_perm2 = 'w';
	result = get_setgid(st, result);
	if (st.st_mode & S_IROTH)
		result->other_perm1 = 'r';
	if (st.st_mode & S_IWOTH)
		result->other_perm2 = 'w';
	result = get_sticky_bit(st, result);
	return (result);
}

t_info		*get_setuid(struct stat st, t_info *result)
{
	if ((st.st_mode & S_IXUSR) && (st.st_mode & S_ISUID))
		result->owner_perm3 = 's';
	else if (!(st.st_mode & S_IXUSR) && (st.st_mode & S_ISUID))
		result->owner_perm3 = 'S';
	else if ((st.st_mode & S_IXUSR) && !(st.st_mode & S_ISUID))
		result->owner_perm3 = 'x';
	return (result);
}

t_info		*get_setgid(struct stat st, t_info *result)
{
	if ((st.st_mode & S_IXGRP) && (st.st_mode & S_ISGID))
		result->group_perm3 = 's';
	else if (!(st.st_mode & S_IXGRP) && (st.st_mode & S_ISGID))
		result->group_perm3 = 'S';
	else if ((st.st_mode & S_IXGRP) && !(st.st_mode & S_ISGID))
		result->group_perm3 = 'x';
	return (result);
}

t_info		*get_sticky_bit(struct stat st, t_info *result)
{
	if ((st.st_mode & S_IXOTH) && (st.st_mode & S_ISVTX))
		result->other_perm3 = 't';
	else if (!(st.st_mode & S_IXOTH) && (st.st_mode & S_ISVTX))
		result->other_perm3 = 'T';
	else if ((st.st_mode & S_IXOTH) && !(st.st_mode & S_ISVTX))
		result->other_perm3 = 'x';
	return (result);
}
