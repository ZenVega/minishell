/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:02:45 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 17:33:38 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


static	get_offset(t_parser_info *p_info, t_app *app, int i_dol, char *pd)
{
	if (*(pd + 1) == '?')
		return (replace_return(app, p_info, i_dol));
	else 
		return (replace_var(app, p_info, pd));
}

void	expand(t_parser_info *p_info, t_app *app, t_cmd_info *cmd)
{
	char	*pd;
	int		i_dol;
	int		offset;

	pd = ft_strchr(p_info->line, '$');
	while (pd != NULL)
	{
		i_dol = pd - p_info->line;
		offset = i_dol + 1;
		if (p_info->mask[i_dol] != 1)
		{
			if (is_space(*(pd + 1)) || *(pd + 1) == '\0' || *(pd + 1) == '"' )
				pd++;
			else 
				offset = get_offset(p_info, app, i_dol, pd);
			create_mask(p_info, &app->malloc_list, cmd);
		}
		if (offset == -1)
			set_err(cmd, ERR_MALLOC, NULL);
		pd = ft_strchr(&p_info->line[offset], '$');
	}
}
