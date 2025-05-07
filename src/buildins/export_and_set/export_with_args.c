/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:19:13 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/05 12:04:15 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_and_set.h"

static int	invalid_identifier(char *arg)
{
	char	*addr_equal;
	int		len;
	int		i;

	if (ft_isdigit(arg[0]) || arg[0] == '=')
		return (1);
	addr_equal = ft_strchr(arg, '=');
	if (addr_equal)
		len = addr_equal - arg;
	else
		len = ft_strlen(arg);
	i = 0;
	while (i < len)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	copy_from_loc_to_envp(char *var_name, t_app *app)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (app->local_var && app->local_var[i])
	{
		if (found_var(app->local_var[i], var_name, var_len))
		{
			app->envp = add_var_to_array(app->envp, app->local_var[i]);
			app->local_var = rm_var_from_array(app->local_var, var_name);
			if (!app->envp || !app->local_var)
				return (-1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	update_or_add_var(char *var_name, char *var_val, t_app *app)
{
	char	*tmp;
	char	*new_var;

	if (var_val)
	{
		tmp = ft_strjoin(var_name, "=");
		if (!tmp)
			return (-1);
		new_var = ft_strjoin(tmp, var_val);
		free(tmp);
	}
	else
		new_var = ft_strdup(var_name);
	if (!new_var)
		return (-1);
	if (update_var_arr(var_name, new_var, app->local_var) == 1
		&& update_var_arr(var_name, new_var, app->envp) == 1)
		app->envp = add_var_to_array(app->envp, new_var);
	free(new_var);
	return (0);
}

int	set_export_var(t_app *app, char *arg)
{
	char	*var_name;
	char	*addr_equal;

	addr_equal = ft_strchr(arg, '=');
	if (addr_equal)
	{
		var_name = ft_substr(arg, 0, addr_equal - arg);
		add_to_malloc_list(&app->malloc_list, var_name);
		return (update_or_add_var(var_name, addr_equal + 1, app));
	}
	else
	{
		var_name = arg;
		if (copy_from_loc_to_envp(var_name, app) == 1)
			return (update_or_add_var(var_name, NULL, app));
		return (0);
	}
}

int	export_with_args(t_app *app, t_cmd_info *cmd)
{
	int	i;
	int	err;

	i = 1;
	err = 0;
	while (cmd->args[i])
	{
		if (invalid_identifier(cmd->args[i]))
		{
			ft_fprintf(2, "minishell: export: `%s`: not a valid identifier\n",
				cmd->args[i]);
			app->ret_val = 1;
		}
		else
		{
			err = set_export_var(app, cmd->args[i]);
		}
		i++;
	}
	return (err);
}
