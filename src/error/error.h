/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:21:13 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 13:27:17 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ERROR_H
# define ERROR_H

# include "../includes/CONSTANTS.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include <string.h>

typedef struct s_err {
	t_err_code	code;
	const char	*msg;
}	t_err;

int		exit_with_error(t_cmd_info cmd);
int		set_err(t_cmd_info *cmd, t_err_code err, char *suspect);

#endif
