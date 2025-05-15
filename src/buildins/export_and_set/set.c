/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 10:07:52 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/14 14:18:21 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_and_set.h"

int	set_var(t_app *app, t_cmd_info *cmd)
{
	char	*addr_equal;
	char	*var_name;
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		addr_equal = ft_strchr(cmd->args[i], '=');
		if (addr_equal)
		{
			var_name = ft_substr(cmd->args[i], 0, addr_equal - cmd->args[i]);
			if (update_var_arr(var_name, cmd->args[i], app->envp) == 1)
			{
				if (update_var_arr(var_name, cmd->args[i], app->local_var) == 1)
					app->local_var
						= add_var_to_array(app->local_var, cmd->args[i]);
			}
			free(var_name);
		}
		i++;
	}
	return (0);
}

static void	unset_var_from_arr(char ***arr, char *arg, int var_len)
{
	int	i;

	i = 0;
	while (arr && (*arr)[i])
	{
		if (found_var((*arr)[i], arg, var_len))
		{
			*arr = rm_var_from_array(*arr, arg);
			break ;
		}
		i++;
	}
}

int	unset_var(t_app *app, t_cmd_info *cmd)
{
	int	j;
	int	var_len;

	j = 1;
	while (cmd->args[j])
	{
		var_len = ft_strlen(cmd->args[j]);
		unset_var_from_arr(&app->envp, cmd->args[j], var_len);
		unset_var_from_arr(&app->local_var, cmd->args[j], var_len);
		j++;
	}
	return (0);
}
