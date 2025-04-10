/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:43:20 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/10 14:29:14 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_dollar(char **args, char **envp)
{
	int	i;
	int j;
	int	len;
	
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			len = ft_strlen(args[i] + 1);
			j = 0;
			while (envp[j])
			{
				if (ft_strncmp(args[i] + 1, envp[j], len) == 0)
				{
					args[i] = ft_strdup(envp[j] + len + 1);
					return ;
				}
				j++;
			}	
		}
		i++;
	}
		
}
