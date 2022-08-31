#ifndef LIBFT_V2_H
# define LIBFT_V2_H

# include <stdio.h>

# include "libft.h"

int     ft_strcmp(const char *s1, const char *s2);

/* utils_2d.c */
int		size_2d(char **arr);
void	free_2d(char **arr);
void	print_2d(char **arr, char delimeter);
char	**dup_2d(char **src_arr);
char	**add_to_2d(char ***old_arr, char *mem, int idx);
char	**rm_from_2d(char ***old_arr, int idx);

#endif
