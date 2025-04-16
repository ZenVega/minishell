/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:18 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/16 12:59:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <string.h>

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
	int		index;
	int		i;

	pivot = array[end];
	index = start;
	i = start;
	while (i < end)
	{
		if (strcmp(array[i], pivot) < 0)
		{	
			swap(&array[i], &array[index]);
			index++;
		}
		i++;
	}
	swap(&array[index], &array[end]);
	return (index);	
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


char	**copy_envp(char **envp)
{
	int		size;
	int		i;
	char	**copy;
	int		j;

	size = 0;
	while (envp[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return NULL;
	i = 0;
	while (envp[i])
	{
		copy[i] = strdup(envp[i]);
		if (!copy[i]) 
		{
            		j = 0;
            		while (j < i) 
            		{
                		free(copy[j]);
                		j++;
            		}
            		free(copy);
            		return NULL;
        	}
		i++;
	}
	copy[i] = NULL;
	return (copy);
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

//testing
/*
int	main(int argc, char **argv, char** envp)
{
	char	**print;
	int		i;

	print = copy_and_qsort(envp);
	i = 0;
	while(print[i])
	{
		printf("%s\n", print[i]);
		i++;
	}
}
*/
