/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:18:44 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 13:28:50 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "error.h"

static const char	*get_error_msg(t_err_code err)
{
	t_err	errors[ERR_COUNT];
	int		i;

	errors[0] = (t_err){.code = ERR_SYNTAX, .msg = ERR_SYNTHAX_MSG};
	errors[1] = (t_err){.code = ERR_NO_FILE, .msg = ERR_NO_FILE_MSG};
	errors[2] = (t_err){.code = ERR_NO_VAR, .msg = ERR_NO_VAR_MSG};
	errors[3] = (t_err){.code = ERR_MALLOC, .msg = ERR_MALLOC_MSG};
	errors[4] = (t_err){.code = ERR_FORK, .msg = ERR_FORK_MSG};
	errors[5] = (t_err){.code = ERR_PIPE, .msg = ERR_PIPE_MSG};
	errors[5] = (t_err){.code = ERR_ARGS, .msg = ERR_ARGS_MSG};
	i = -1;
	while (++i < ERR_COUNT)
		if (errors[i].code == err)
			return (errors[i].msg);
	return ("unknown error");
}

int	exit_with_error(t_cmd_info cmd)
{
	if (cmd.err_info.suspect)
		ft_fprintf(2, "minishell: %s: %s\n",
			cmd.err_info.suspect, get_error_msg(cmd.err_info.code));
	else
		ft_fprintf(2, "minishell: %s\n",
			get_error_msg(cmd.err_info.code));
	return (-1);
}

int	set_err(t_cmd_info *cmd, t_err_code err, char *suspect)
{
	if (suspect != NULL && suspect[0] != '\0')
		cmd->err_info.suspect = ft_strdup(suspect);
	cmd->err_info.code = err;
	return (-1);
}
