/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:02:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/30 16:54:24 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int open_pipe(t_app *app, t_cmd_info *cmd)
{
    pid_t pids[2];
    int fd[2];
    t_parser_info p_info;
    int err = 0;

    if (pipe(fd) < 0)
        return set_err(cmd, ERR_PIPE, NULL);

    // left side of pipe
    pids[0] = fork();
    if (pids[0] == -1)
        return set_err(cmd, ERR_FORK, NULL);
    else if (pids[0] == 0)
    {
        // Writer child: executes cmd->args[0], writing to fd[1]
        close(fd[0]); // Close unused read end
        p_info = init_parser_info(cmd->infile, fd[1], cmd->args[0]);
        exe(app, parser(p_info, &app->malloc_list));
        close(fd[1]); // Close write end after use
        exit(0);
    }

    // right side of pipe
    pids[1] = fork();
    if (pids[1] == -1)
        return set_err(cmd, ERR_FORK, NULL);
    else if (pids[1] == 0)
    {
        // Reader child: executes cmd->args[1], reading from fd[0]
        close(fd[1]); // Close unused write end
        p_info = init_parser_info(fd[0], cmd->outfile, cmd->args[1]);
        exe(app, parser(p_info, &app->malloc_list));
        close(fd[0]); // Close read end after use
        exit(0);
    }

    //  Parent process
    close(fd[0]);
    close(fd[1]);

    // Wait for both children to finish
    waitpid(pids[0], NULL, 0);
    waitpid(pids[1], NULL, 0);

    app->ret_val = err;
    return err;
}

