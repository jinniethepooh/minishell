#ifndef LIBFT_V2_H
# define LIBFT_V2_H

# include <stdio.h>

# include "libft.h"

int     ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);

/* utils_instr.c */
int		count_in_str(char *str, char c);
int		pos_in_str(char *str, char c);
int 	ft_isspace(char c);
int		ft_isspace_str(char *s);

/* utils_2d.c */
int		size_2d(char **arr);
void	free_2d(char **arr);
void	print_2d(char **arr, char delimeter);
char	**dup_2d(char **src_arr);
char	**add_to_2d(char ***old_arr, char *mem, int idx);
char	**rm_from_2d(char ***old_arr, int idx);
char	**map_2d(char ***arr, void (*f)(char **));

#endif
