
#include "exit.h"

int	ft_exit(t_app *app, t_cmd_info *cmd)
{
	int     err;
    
    if (cmd->args[1] && ft_isdigit(cmd->args[1][0]))
        err = cmd->args[1][0];
    else
        err = 0;
    free_malloc_list(app);
    free_envp(app->envp);
    free(app->prompt);
    free(app);
    exit(err);
	return (err);
}