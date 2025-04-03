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

const char	*get_error_msg(t_err_code err)
{
	t_err	errors[ERR_COUNT];
	int		i;

	errors[0] = (t_err){.code = ERR_SYNTAX, .msg = ERR_SYNTHAX_MSG};
	errors[1] = (t_err){.code = ERR_NO_FILE, .msg = ERR_NO_FILE_MSG};
	i = 0;
	while (i < ERR_COUNT)
	{
		if (errors[i].code == err)
			return (errors[i].msg);
		i++;
	}
	return ("unknown error");
}

void	exit_with_error(t_cmd_info cmd)
{
	if (cmd.err_info.suspect)
	{
		ft_fprintf(2, "minishell: %s: %s\n",
			cmd.err_info.suspect, get_error_msg(cmd.err_info.code));
	}
	else
		ft_fprintf(2, "minishell: %s\n",
			get_error_msg(cmd.err_info.code));
}
