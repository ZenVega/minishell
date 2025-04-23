/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:24:14 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/16 09:50:06 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" 

int	is_space(char c)
{
	if (
		c == ' '
		|| c == '\b'
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
	) 
		return (1);
	return (0);
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
		copy[i] = ft_strdup(envp[i]);
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




