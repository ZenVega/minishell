/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_white_safe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:48:10 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/20 15:25:32 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_space_count(char const *s, int *mask)
{
	int	i;
	int	count;
	int	breaker;

	i = 0;
	count = 0;
	breaker = 1;
	while (s[i])
	{
		if ((!ft_iswhitespace(s[i]) || mask[i]) && breaker)
		{
			count++;
			breaker = 0;
		}
		else if (ft_iswhitespace(s[i]) && !mask[i])
			breaker = 1;
		i++;
	}
	return (count);
}

static int	get_str_len(char const *s, int *mask)
{
	int	i;

	i = 0;
	while (s[i] && (!ft_iswhitespace(s[i]) || mask[i]))
		i++;
	return (i);
}

static char	*get_str(char const *s, int l)
{
	int		j;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (l + 1));
	if (!buffer)
		return (NULL);
	j = 0;
	while (j < l)
	{
		buffer[j] = s[j];
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

static void	*free_all(int i, char **arr)
{
	while (i >= 0)
		free(arr[i--]);
	free(arr);
	return (NULL);
}

char	**ft_split_white_safe(char const *s, int *mask)
{
	char	**arr;
	int		count;
	int		i;
	int		j;
	int		len;

	count = get_space_count(s, mask);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		while (ft_iswhitespace(s[j]) && !mask[j])
			j++;
		len = get_str_len(s + j, mask + j);
		if (len)
			arr[i++] = get_str(s + j, len);
		if (arr[i - 1] == NULL)
			return (free_all((i - 1), arr));
		j += len;
	}
	arr[i] = NULL;
	return (arr);
}
