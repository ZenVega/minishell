/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:24:14 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 16:14:07 by uschmidt         ###   ########.fr       */
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

void	exit_with_error(int err)
{
	if (err)
		perror("Minishell: Process exited with err: ");
}
