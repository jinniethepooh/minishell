#include "libft_v2.h"

int	size_2d(char **arr)
{
	int	size;

	size = 0;
	if (arr)
		while (arr[size])
			size++;
	return (size);
}

void	free_2d(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	print_2d(char **arr, char delimeter)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			printf("%s", arr[i]);
			if (arr[++i])
				printf("%c", delimeter);
		}
		i++;
	}
}

char	**dup_2d(char **src_arr)
{
	char	**new_arr;
	int		i;

	if (!src_arr)
		return (0);
	new_arr = malloc((size_2d(src_arr) + 1) * sizeof(*new_arr));
	i = 0;
	while (src_arr[i])
	{
		new_arr[i] = ft_strdup(src_arr[i]);
		i++;
	}
	new_arr[i] = 0;
	return (new_arr);
}

char	**add_to_2d(char ***old_arr, char *mem, int idx)
{
	char	**new_arr;
	int		i;
	int		j;

	if (!*old_arr)
		return (0);
	if (idx >= size_2d(*old_arr))
		idx = size_2d(*old_arr);
	new_arr = malloc((size_2d(*old_arr) + 2) * sizeof(*new_arr));
	i = 0;
	j = 0;
	while ((*old_arr)[i])
	{
		if (i == idx)
			j++;
		new_arr[j++] = ft_strdup((*old_arr)[i++]);
	}
	new_arr[idx] = mem;
	new_arr[i + 1] = 0;
	free_2d(*old_arr);
	*old_arr = new_arr;
	return (*old_arr);
}

char	**rm_from_2d(char ***old_arr, int idx)
{
	char	**new_arr;
	int		i;
	int		j;

	if (!*old_arr)
		return (0);
	if (idx >= size_2d(*old_arr))
		return (*old_arr);
	new_arr = malloc(size_2d(*old_arr) * sizeof(*new_arr));
	i = 0;
	j = 0;
	while ((*old_arr)[i])
	{
		if (i != idx)
			new_arr[j++] = ft_strdup((*old_arr)[i]);
		i++;
	}
	new_arr[j] = 0;
	free_2d(*old_arr);
	*old_arr = new_arr;
	return (*old_arr);
}
