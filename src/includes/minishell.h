/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:28:24 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/12 14:06:39 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_cmd_type {
	LOGICAL,
	PIPE,
	BIN
}	t_cmd_type;

typedef struct s_cmd_info
{
	int			infile;
	int			outfile;
	char		**args;
	t_cmd_type	type;
}	t_cmd_info;

typedef struct s_app
{
	t_list	*malloc_list;
	char	*envp[];
}	t_app;
