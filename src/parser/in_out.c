/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:21:47 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/19 11:25:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

//getting the split input
//looking for > and < to set infile and output
void	in_out(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	set_infile(args, cmd, malloc_list);
	set_outfile(args, cmd, malloc_list);
	//trim_args(args);
}

// finding > in splits and set infile
//options: 1) >infile 2) > infile
void	set_infile(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	int		i;
	char	*file_name;

	i = 0;
	while (args[i])
	{	
		if (args[i][0] == '<')
		{
			// case < infile
			if (ft_strlen(args[i]) == 1)
			{
				if (args[i + 1])
					file_name = args[i + 1];
				else
					parse_error_near_nl(malloc_list);
				cmd->infile = open(file_name, O_RDONLY);
				if (cmd->infile < 0)
					no_infile(file_name, malloc_list);
			}
			if (ft_strlen(args[i]) > 1)
			{
				// case <infile
				if (args[i][1] != '<')
				{
					file_name = ft_strtrim(args[i], (const char *) "<");
					add_to_malloc_list(malloc_list, (void *) file_name);
					cmd->infile = open(file_name, O_RDONLY);
					if (cmd->infile < 0)
						no_infile(file_name, malloc_list);
				}
				//here_doc <<
				//if (args[i][1] == '<')
					//here_doc(args, i, cmd, malloc_list);	
			}	
		}
	i++;
	}	
}

//problem: here_doc muss vermutlich readline verwenden, statt get_next_line
// options: ">>END" and ">>" "END"
/*
void	here_doc(char **args, int i, t_cmd_info *cmd, t_list **malloc_list)
{
	int		fd;
	char	*limiter;
	char	*next_line;

	if (args[i + 1])
		limiter = args[i + 1];
	// what happens on single << without delimiter? - parser error near new_line
	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777);
	while (1)
	{
		next_line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(limiter, next_line, ft_strlen(limiter)) == 0)
		{
			free(next_line);
			close(fd);
			cmd->infile = fd; 
			return ;
		}
		write(fd, next_line, ft_strlen(next_line));
		free(next_line);
	}
	return ;
}
*/

void	set_outfile(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	int		i;
	char	*file_name;

	i = 0;
	while (args[i])
	{	
		if (args[i][0] == '>')
		{
			// case > outfile
			if (ft_strlen(args[i]) == 1)
			{
				if (args[i + 1])
					file_name = args[i + 1];
				else
					parse_error_near_nl(malloc_list);
				cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if (cmd->outfile < 0)
					no_infile(file_name, malloc_list);
			}
			if (ft_strlen(args[i]) > 1)
			{
				// case >outfile
				if (args[i][1] != '>')
				{
					file_name = ft_strtrim(args[i], (const char *) ">");
					add_to_malloc_list(malloc_list, (void *) file_name);
					cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
					if (cmd->outfile < 0)
						no_infile(file_name, malloc_list);
				}	
			}	
		}
	i++;
	}	
}