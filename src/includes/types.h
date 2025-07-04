/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:49:38 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/21 15:37:15 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../libft/libft.h"
# include "CONSTANTS.h"
# include <signal.h>

typedef struct s_app
{
	t_list				*malloc_list;
	t_list				*hds;
	char				**envp;
	char				**local_var;
	char				*prompt;
	int					ret_val;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
}	t_app;

typedef struct s_heredoc
{
	char	*del;
	char	*doc_name;
	int		fd;
}	t_heredoc;

typedef enum e_cmd_type {
	UNDEFINED = 0,
	LOGICAL = 1,
	PIPE = 2,
	BIN = 3
}	t_cmd_type;

typedef struct s_err_info {
	t_err_code	code;
	char		*suspect;
}	t_err_info;

typedef struct s_cmd_info
{
	int			infile;
	int			outfile;
	int			infile_backup;
	int			outfile_backup;
	char		**args;
	t_err_info	err_info;
	t_cmd_type	type;
}	t_cmd_info;

typedef struct s_parser_info
{
	int			infile;
	int			outfile;
	char		*line;
	int			*mask;
}	t_parser_info;

#endif
