/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/21 15:52:29 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// finding > in splits and set infile
//options: 1) >infile 2) > infile

// circling through all the argument parts,
//multiple infiles are just overwritten by following
int	set_infile(t_app *app, char **args, t_cmd_info *cmd)
{
	int		i;
	int		err;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<')
		{
			err = found_infile(app, args, i, cmd);
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);
}

static int	is_heredoc(t_app *app, char *file_name)
{
	t_list		*hd_list;
	t_heredoc	*hd;

	hd_list = app->hds;
	while (hd_list)
	{
		hd = hd_list->content;
		if (!ft_strncmp(hd->doc_name, file_name, ft_strlen(file_name)))
			return (1);
		hd_list = hd_list->next;
	}
	return (0);
}

static int	simple_infile(t_app *app, char *file_name, t_cmd_info *cmd)
{
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	cmd->infile = open(clean_filename(file_name), O_RDONLY);
	if (cmd->infile < 0)
		return (set_err(cmd, ERR_NO_FILE, file_name));
	if (is_heredoc(app, file_name))
		unlink(file_name);
	return (0);
}

int	found_infile(t_app *app, char **args, int i, t_cmd_info *cmd)
{
	char	*file_name;

	file_name = NULL;
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "after <"));
		return (simple_infile(app, file_name, cmd));
	}
	return (0);
}
