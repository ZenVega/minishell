/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:18 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/29 12:34:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		partition(char **array, int start, int end)
{
	char	*pivot;
	int		pivot_pos;
	int		i;

	pivot = array[end];
	pivot_pos = start;
	i = start;
	while (i < end)
	{
		if (ft_strcmp(array[i], pivot) < 0)
		{	
			swap(&array[i], &array[pivot_pos]);
			pivot_pos++;
		}
		i++;
	}
	swap(&array[pivot_pos], &array[end]);
	return (pivot_pos);	
}

void	quicksort(char **array, int start, int end)
{	
	int	pivot_pos;
	
	if (start < end)
	{
		pivot_pos = partition(array, start, end);
		quicksort(array, start, pivot_pos - 1);
		quicksort(array, pivot_pos + 1, end);
	}
}

char	**copy_and_qsort(char **array)
{
	char	**sorted;
	int	size;
	
	sorted = copy_envp(array);
	if (!sorted)
		return (NULL);
	size = 0;
	while(sorted[size])
		size++;
	quicksort(sorted, 0, size - 1);
	return (sorted); 	
}

