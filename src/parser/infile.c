#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

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