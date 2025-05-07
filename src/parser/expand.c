/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/05 14:58:40 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	remove_var(t_parser_info *p_info)
{
	int	i;
	int	j;

	i = 0;
	while (p_info->line[i] && p_info->line[i] != '$')
		i++;
	j = i++;
	while (p_info->line[i] && !is_space(p_info->line[i]))
		i++;
	while (p_info->line[i])
		p_info->line[j++] = p_info->line[i++];
	while (p_info->line[j])
		p_info->line[j++] = 0;
	return (0);
}

static int	expand_var(t_app *app, t_parser_info *p_info, char *var, int var_len)
{
	int		len_newline;
	int		i;
	int		j;
	int		k;
	char	*ret_val;

	i = -1;
	j = -1;
	len_newline = ft_strlen(p_info->line) - var_len;
	len_newline += ft_strlen(var) - var_len - 1;
	ret_val = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
		* len_newline + 1);
	if (!ret_val)
		return (1);
	while (p_info->line[++i] && (p_info->line[i] != '$' ||  p_info->mask[i] == 1))
		ret_val[i] = p_info->line[i];
	k = i + var_len + 1;
	var += var_len + 1;
	while (var[++j])
		ret_val[i++] = var[j];
	while (i < len_newline)
		ret_val[i++] = p_info->line[k++];
	p_info->line = ret_val;
	return (0);
}

static int	replace_return(t_app *app, t_parser_info *p_info, int i$)
{
	char	*ret_val;
	char	*var;
	int		index[2];

	var = ft_itoa(app->ret_val);
	if (var == NULL)
		return (1);
	ret_val = (char *)malloc_and_add_list(&app->malloc_list, sizeof(char)
		* (ft_strlen(p_info->line) + ft_strlen(var) - 1));
	if (!ret_val)
		return (1);
	index[0] = -1;
	index[1] = 0;
	while (++index[0] < i$)
		ret_val[index[0]] = p_info->line[index[0]];
	while (var[index[1]])
		ret_val[index[0]++] = var[index[1]++];
	index[1] = index[0] - index[1] + 2;
	while (p_info->line[index[1]])
		ret_val[index[0]++] = p_info->line[index[1]++];
	ret_val[index[0]] = '\0';
	p_info->line = ret_val;
	return (0);
}

static int	replace_var(t_app *app, t_parser_info *p_info, char *p$)
{
	int	var_len;
	int	i;

	i = -1;
	var_len = 1;
	while (p$[var_len] && p$[var_len] != '$' && p$[var_len] != ' ')
		var_len++;
	while (--var_len > 0)
	{
		while (app->envp[++i])
			if (!ft_strncmp(p$ + 1, app->envp[i], var_len)
				&& (app->envp[i][var_len] == '=' || app->envp[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->envp[i], var_len)); 
		i = -1;
		while (app->local_var[++i])
			if (!ft_strncmp(p$ + 1, app->local_var[i], var_len)
				&& (app->envp[i][var_len] == '=' || app->envp[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->local_var[i], var_len)); 
	}
	return (remove_var(p_info));
}

int	expand(t_parser_info *p_info, t_app *app, t_cmd_info *cmd)
{
	char	*p$;
	int		i$;

	p$ = ft_strchr(p_info->line, '$');
	while (p$ != NULL && *(p$ + 1) != '\0')
	{
		i$ = p$ - p_info->line;
		if (p_info->mask[i$] != 1)
		{
			if (*(p$ + 1) == '?')
			{
				if (replace_return(app, p_info, i$))
					set_err(cmd, ERR_MALLOC, NULL);
			}
			else if (replace_var(app, p_info, p$))
				set_err(cmd, ERR_MALLOC, NULL);
		}
		create_mask(p_info, &app->malloc_list, cmd);
		p$ = ft_strchr(&p_info->line[i$ + 1], '$');
	}
	return (0);
}
