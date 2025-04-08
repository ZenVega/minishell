/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 13:37:35 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "../libft/libft.h"
# include <signal.h>

typedef struct s_app
{
	t_list	*malloc_list;
	char	**envp;
	char	*prompt;
	struct sigaction sa_init;
	struct sigaction sa_quit;
}	t_app;

typedef enum e_cmd_type {
	UNDEFINED = 0,
	LOGICAL = 1,
	PIPE = 2,
	BIN = 3
}	t_cmd_type;

typedef struct s_cmd_info
{
	int			infile;
	int			outfile;
	char		**args;
	int			error_msg;
	t_cmd_type	type;
}	t_cmd_info;

//TODO: error msg is an integer. We need to include an error message lookup table
typedef struct s_parser_info
{
	int			infile;
	int			outfile;
	char		*line;
}	t_parser_info;
#endif
