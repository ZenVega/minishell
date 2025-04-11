/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:53:37 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/10 11:54:54 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

// possible args:
// hello world
// "hello world"
// "hello world
// hello "world"
// hello $world
// hello "$world"
// "hello $world"
// 'hello $world'
int	echo(t_app *app, t_cmd_info *cmd)
{
	int		err;
	char	**args;

	err = 0;
	if (!app)
		return (err);
	args = cmd->args + 1;
	ft_printf("%s\n", args[0]);
	return (err);
}
