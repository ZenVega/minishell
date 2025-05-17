/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/14 13:46:53 by jhelbig          ###   ########.fr       */
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

static int	expand_var(t_app *app, t_parser_info *p_info, 
		char *var, int var_len)
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
		return (-1);
	while (p_info->line[++i]
		&& (p_info->line[i] != '$' || p_info->mask[i] == 1))
		ret_val[i] = p_info->line[i];
	k = i + var_len + 1;
	var += var_len + 1;
	while (var[++j])
		ret_val[i++] = var[j];
	j = i;
	while (i < len_newline)
		ret_val[i++] = p_info->line[k++];
	p_info->line = ret_val;
	return (j);
}

static int	replace_return(t_app *app, t_parser_info *p_info, int i_dol)
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
	while (++index[0] < i_dol)
		ret_val[index[0]] = p_info->line[index[0]];
	while (var[index[1]])
		ret_val[index[0]++] = var[index[1]++];
	index[1] = index[0] - index[1] + 2;
	free(var);
	while (p_info->line[index[1]])
		ret_val[index[0]++] = p_info->line[index[1]++];
	ret_val[index[0]] = '\0';
	p_info->line = ret_val;
	return (0);
}

static int	replace_var(t_app *app, t_parser_info *p_info, char *p_dol)
{
	int	var_len;
	int	i;

	i = -1;
	var_len = 1;
	while (p_dol[var_len] && p_dol[var_len] != '$' && p_dol[var_len] != ' ')
		var_len++;
	while (--var_len > 0)
	{
		while (app->envp[++i])
			if (!ft_strncmp(p_dol + 1, app->envp[i], var_len)
				&& (app->envp[i][var_len] == '='
				|| app->envp[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->envp[i], var_len)); 
		i = -1;
		while (app->local_var[++i])
			if (!ft_strncmp(p_dol + 1, app->local_var[i], var_len)
				&& (app->local_var[i][var_len] == '='
				|| app->local_var[i][var_len] == '\0'))
				return (expand_var(app, p_info, app->local_var[i], var_len)); 
	}
	return (remove_var(p_info));
}

int	expand(t_parser_info *p_info, t_app *app, t_cmd_info *cmd)
{
	char	*p_dol;
	int		i_dol;
	int		offset;

	p_dol = ft_strchr(p_info->line, '$');
	while (p_dol != NULL)
	{
		i_dol = p_dol - p_info->line;
		offset = i_dol + 1;
		if (p_info->mask[i_dol] != 1)
		{
			if (is_space(*(p_dol + 1)) || *(p_dol + 1) == '\0'
				|| *(p_dol + 1) == '"' )
				p_dol++;
			else 
			{
				if (*(p_dol + 1) == '?')
				{
					if (replace_return(app, p_info, i_dol))
						set_err(cmd, ERR_MALLOC, NULL);
				}
				else 
				{
					offset = replace_var(app, p_info, p_dol);
					if (offset == -1)
						set_err(cmd, ERR_MALLOC, NULL);
				}
			}
			create_mask(p_info, &app->malloc_list, cmd);
		}
		p_dol = ft_strchr(&p_info->line[offset], '$');
	}
	return (0);
}
