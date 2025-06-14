/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:47:31 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/21 15:55:08 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd_info	*on_success(t_cmd_info *cmd, char **parts)
{
	cmd->args = parts;
	cmd->type = PIPE;
	return (cmd);
}

static int	mask_and_expantion(
		t_parser_info *p_info, t_app *app, t_cmd_info *cmd)
{
	int			err;

	free(p_info->mask);
	err = create_mask(p_info, &app->malloc_list, cmd);
	if (err == -1)
		return (-1);
	err = create_heredoc(app, p_info, cmd);
	if (err)
		return (-1);
	expand(p_info, app, cmd);
	return (0);
}

t_cmd_info	*parser(t_parser_info p_info, t_app *app)
{
	t_cmd_info	*cmd;
	char		**parts;
	int			err;

	cmd = cmd_info_init(&app->malloc_list, &p_info);
	if (!cmd)
		return (set_err(cmd, ERR_MALLOC, ""), cmd);
	if (mask_and_expantion(&p_info, app, cmd))
		return (NULL);
	parts = (char **)malloc_and_add_list(&app->malloc_list, sizeof(char *) * 3);
	if (!parts)
		return (NULL);
	err = pipe_split(parts, &p_info, &app->malloc_list);
	if (err == -1)
		return (NULL);
	if (err == 0)
		return (on_success(cmd, parts));
	cmd->type = BIN;
	err = set_io_files(p_info.line, cmd, app, p_info.mask);
	if (err != 0)
		app->ret_val = err;
	return (cmd);
}
