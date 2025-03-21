#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"

void	set_outfile(char **args, t_cmd_info *cmd, t_list **malloc_list)
{
	int		i;

	i = 0;
	while (args[i])
	{	
		if (args[i][0] == '>')
            found_outfile(args, i, cmd, malloc_list);
	i++;
	}	
}

void    found_outfile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list)
{
    char    *file_name;

    file_name = NULL;
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			parse_error_near_nl(malloc_list);
        truncate_outfile(file_name, cmd, malloc_list);
	}
	else if (ft_strlen(args[i]) > 1)
	{
	    // case >outfile
		if (args[i][1] != '>')
		{
			file_name = ft_strtrim(args[i], (const char *) ">");
			add_to_malloc_list(malloc_list, (void *) file_name);
            truncate_outfile(file_name, cmd, malloc_list);
		}
        //case_append outfile >>
		else if (args[i][1] == '>')
            append_outfile(args, i, cmd, malloc_list);
	}	
}

void    truncate_outfile(char *file_name, t_cmd_info *cmd, t_list **malloc_list)
{
    cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (cmd->outfile < 0)
        //could not open outfile error here
		no_infile(file_name, malloc_list);
}

void append_outfile(char **args, int i, t_cmd_info *cmd, t_list **malloc_list)
{
	char	*file_name;

    // case >> outfile
    if (ft_strlen(args[i]) == 2)
    {
        if (args[i + 1])
			file_name = args[i + 1];
        else
			parse_error_near_nl(malloc_list);
		cmd->outfile = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->outfile < 0)
			no_infile(file_name, malloc_list);
    }
    // case >>outfile
    else
    {
        file_name = ft_strtrim(args[i], (const char *) ">");
		add_to_malloc_list(malloc_list, (void *) file_name);
		cmd->outfile = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (cmd->outfile < 0)
			no_infile(file_name, malloc_list);
    }
}
