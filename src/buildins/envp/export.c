/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:45 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/30 12:13:55 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	export_no_args(t_app *app)
{
	char	**print;
	int		i;
	char	*addr_equal;
	char	*substr;

	print = copy_and_qsort(app->envp);
	if (!print)
		return (-1);
	i = 0;
	while (print[i])
	{
		addr_equal = ft_strchr(print[i], '=');
		//print until and including = then "var_val"
		if (addr_equal != NULL)
		{	
			substr = ft_substr(print[i], 0, (size_t)(addr_equal - print[i] + 1));
			ft_printf("declare -x %s\"%s\"\n", substr, addr_equal + 1);
			free(substr);
		}
		else
			ft_printf("declare -x %s\n", print[i]);
		i++;
	}
	free_envp(print);
	app->ret_val = 0;
	return (0);
}

int	invalid_identifier(char *arg)
{
	int		c;
	char	*addr_equal;
	int		len;
	int		i;

	addr_equal = ft_strchr(arg, '=');
	if (!addr_equal)
		len = ft_strlen(arg);
	else
		len = addr_equal - arg;
	i = 0;
	while (i < len)
	{
		c = arg[i];
		if (!(ft_isdigit(c) || ft_isalpha(c) || c == '_'))
			return (1);
		i++;	
	}
	return (0);
}

char	**add_var_to_envp(char **envp, char *new_var)
{
	int		size;
	int		i;
	char	**new;

	size = 0;
	while (envp[size])
		size++;
	new = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		if (!new[i]) 
		{
			free_envp(new);
			return (NULL);
		}
		i++;
	}
	new[i++] = new_var;
	new[i] = NULL;
	free_envp(envp);
	return (new);
}

int	update_or_set_new_var(char *var_name, char *var_val, t_app *app)
{
	int		i;
	char	*tmp;
	char 	*new_var;
	
	if (var_val != NULL)
	{
		tmp = ft_strjoin(var_name, "=");
		new_var = ft_strjoin(tmp, var_val);
		free(tmp);
	}
	else
		new_var = ft_strdup(var_name);
	i =  0;
	while (app->envp[i])
	{
		if (ft_strncmp(app->envp[i], var_name, ft_strlen(var_name)) == 0
				&& (app->envp[i][ft_strlen(var_name)] == '=' 
				|| app->envp[i][ft_strlen(var_name)] == '\0'))	
		{
			free(app->envp[i]);
			app->envp[i] = new_var;
			free(var_name);
			return (0);
		}
		i++;
	}
	app->envp = add_var_to_envp(app->envp, new_var);
	if (var_val != NULL)
		free(var_name);
	return (0);
}

int set_var(t_app *app, char *arg)
{
	char	*var_name;
	char	*addr_equal;
	
	addr_equal = ft_strchr(arg, '=');
	if (addr_equal != NULL)
	{
		var_name = ft_substr(arg, 0, (size_t)(addr_equal - arg));
		return (update_or_set_new_var(var_name, addr_equal + 1, app));
	}
	else
	{
		var_name = arg;
		return (update_or_set_new_var(var_name, NULL, app));
	}
}

int	export_with_args(t_app *app, t_cmd_info *cmd)
{
	int	i;
	int err;
	
	err = 0;
	i = 1;
	while (cmd->args[i])
	{
		//if var name invalid
		// just before the =
		if (ft_isdigit(cmd->args[i][0]) == 1
			|| cmd->args[i][0] == '='
			|| invalid_identifier(cmd->args[i]) == 1) 

		{
			ft_fprintf(2, "minishell: export: '%s': not a valid identifier\n", cmd->args[i]);
			app->ret_val = 1;
		}
		//if var="val"
		// or just var
		else
			err = set_var(app, cmd->args[i]);
		//if var

		i++;
	}
	return (err);
}

int	ft_export(t_app *app, t_cmd_info *cmd)
{
	if (!cmd->args[1])
		return (export_no_args(app));
	else
		return (export_with_args(app, cmd));
	return (0);
}
