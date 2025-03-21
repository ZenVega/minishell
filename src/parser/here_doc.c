#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

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