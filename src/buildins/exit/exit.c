
#include "exit.h"
// exit $? = 0
//exit 4 $? = 4

//exit ab 
//exit \n bash: exit: ab: numeric argument required
//$? = 2

//exit 7 5
//exit
//bash: exit: too many arguments
//$? = 1


int	ft_exit(t_app *app, t_cmd_info *cmd)
{
	int     err;

    //too many arguments
    if (cmd->args[2])
    {
        err = 1;
        ft_fprintf(1, "exit\n");
        ft_fprintf(2, "minishell: exit: too many arguments\n");
    }
    //non-numeric argument
    else if (cmd->args[1])
        if (!ft_isnumber(cmd->args[1]))
        {
            err = 2;
            ft_fprintf(1, "exit\n");
            ft_fprintf(2, "minishell: exit: %s: numeric argument requiered\n", cmd->args[1]);
        }
        else
            err = ft_atoi(cmd->args[1]);
    else
        err = 0;
    free_malloc_list(app);
    free_envp(app->envp);
    free(app->prompt);
    free(app);
    exit(err);
	return (err);
}
