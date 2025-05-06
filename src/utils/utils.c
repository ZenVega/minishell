/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:24:14 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/05 10:03:29 by jhelbig          ###   ########.fr       */
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

	size = 0;
	while (envp[size])
		size++;
	copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i]) 
		{
			free_var_arr(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	reroute_io(int input, int output)
{
	if (input != STDIN_FILENO)
		dup2(input, STDIN_FILENO);
	if (output != STDOUT_FILENO)
		dup2(output, STDOUT_FILENO);
}
