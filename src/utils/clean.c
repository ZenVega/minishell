/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:31:14 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/13 16:31:45 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	remove_quotes(char *scnd, char *arg, int pos)
{
	while (scnd >= arg + ++pos)
		arg[pos] = arg[pos + 1];
	pos--;
	while (arg[++pos])
		arg[pos - 2] = arg[pos];
	arg[pos - 1] = 0;
	arg[pos - 2] = 0;
}

int	clean_arg(char *arg)
{
	int		j;
	char	c;
	char	*scnd;

	j = 0;
	while (arg[j])
	{
		while (arg[j] && arg[j] != '"' && arg[j] != '\'')
			j++;
		if (!arg[j])
			return (0);
		c = arg[j];
		scnd = ft_strchr(arg + j + 1, c);
		j--;
		if (scnd == NULL)
			return (0);
		else
		{
			remove_quotes(scnd, arg, j);
			j += (scnd - &arg[j] - 1);
		}
	}
	return (0);
}

int	clean_args(t_cmd_info *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i] != NULL)
	{
		clean_arg(cmd->args[i]);
		i++;
	}
	return (0);
}
