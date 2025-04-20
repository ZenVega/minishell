/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 16:49:48 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/20 16:50:52 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	mask_substr(char *line, int pos, int *mask, char c)
{
	char	*tmp;
	int		mask_id;

	mask_id = 1;
	if (c == '"')
		mask_id = 2;
	tmp = ft_strchr(((&line[pos]) + 1), c);
	if (tmp == NULL)
	{
		mask[pos] = 0;
		return (pos + 1);
	}
	else
		while (line + pos <= tmp)
			mask[pos++] = mask_id;
	return (pos);
}

int	create_mask(t_parser_info *p_info, t_list **malloc_list, t_cmd_info *cmd)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(p_info->line);
	p_info->mask = (int *)malloc_and_add_list(malloc_list, sizeof(int) * len);
	if (!p_info->mask)
		return (set_err(cmd, ERR_MALLOC, NULL));
	while (p_info->line[i])
	{
		while (p_info->line[i]
			&& p_info->line[i] != '"' && p_info->line[i] != '\'')
			p_info->mask[i++] = 0;
		if (p_info->line[i] == '"' || p_info->line[i] == '\'')
			i = mask_substr(p_info->line, i, p_info->mask, p_info->line[i]);
	}
	//ft_printf("MASK: ", p_info->mask[i]);
	//for (int i = 0; i < len; i++)
	//	ft_printf("%d", p_info->mask[i]);
	//ft_printf("\n", p_info->mask[i]);
	return (0);
}

