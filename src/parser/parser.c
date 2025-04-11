/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:47:31 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/02 11:03:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	create_mask(t_parser_info p_info, t_list **malloc_list, t_cmd_info *cmd)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	len = ft_strlen(p_info.line);
	p_info.mask = (int *)malloc_and_add_list(malloc_list, sizeof(int) * len);
	if (!p_info.mask)
		return (set_err(cmd, ERR_MALLOC, NULL));
	while (p_info.line[i])
	{
		while (p_info.line[i] != '"' && p_info.line[i] != '\'')
			p_info.mask[i++] = 0;
		if (p_info.line[i] == '"')
		{
			tmp = ft_strchr((p_info.line + i), '"');
			if (tmp == NULL)
				p_info.mask[i++] = 0;
			else
				while (p_info.line + i <= tmp)
					p_info.mask[i++] = 2;
		}
		if (p_info.line[i] == '\'')
		{
			tmp = ft_strchr((p_info.line + i), '\'');
			if (tmp == NULL)
				p_info.mask[i++] = 0;
			else
				while (p_info.line + i <= tmp)
					p_info.mask[i++] = 1;
		}
	}
	for (int i = 0; i <= len; i++)
		ft_printf("%d-", p_info.mask[i]);
	return (0);
}

t_cmd_info	*parser(t_parser_info p_info, t_list **malloc_list)
{
	t_cmd_info	*cmd;
	char		**parts;
	int			err;

	cmd = cmd_info_init(malloc_list, &p_info);
	if (!cmd)
		return (NULL);
	//find pipe, split on first pipe
	parts = (char **)malloc_and_add_list (malloc_list, sizeof(char *) * 3);
	err = create_mask(p_info, malloc_list, cmd);
	if (err == -1 || !parts)
		return (NULL);
	err = pipe_split(parts, p_info.line, malloc_list);
	//pipe failed
	if (err == -1)
		return (NULL);
	//pipe exists
	if (err == 0)
	{
		cmd->args = parts;
		cmd->type = PIPE;
		return (cmd);
	}
	cmd->type = BIN;
	err = set_io_files(p_info.line, cmd, malloc_list);
	if (err != 0)
		return (NULL);
	return (cmd);
}
