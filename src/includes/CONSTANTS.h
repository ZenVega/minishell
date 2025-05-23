/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CONSTANTS.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:47:17 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:26:21 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define ROOT_PROMPT_BLUE "\x1b[1;34mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_VIOLET "\x1b[1;95mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_PINK "\x1b[1;38;2;255;20;147mmini\x1b[0m🐚: \x1b[1m"

# define ERR_SYNTHAX_MSG "Found syntax error"
# define ERR_NO_FILE_MSG  "No such file or directory"
# define ERR_NO_CMD_MSG  "command not found"
# define ERR_NO_VAR_MSG  "No such variable"
# define ERR_MALLOC_MSG "Cannot allocate memory"
# define ERR_FORK_MSG "Cannot fork a process"
# define ERR_PIPE_MSG "Pipe failed"
# define ERR_ARGS_MSG "Wrong number of arguments"
# define ERR_MANY_ARGS_MSG "too many arguments"
# define ERR_NUM_ARGS_MSG "numeric argument required"
# define ERR_IS_FOLDER_MSG "Is a directory"
# define ERR_IS_NO_FOLDER_MSG "Is not a directory"
# define ERR_PERM_MSG "Permission denied"
# define ERR_IDENT_MSG "not a valid identifier"

# define BUFFER_SIZE 10
# define ERR_COUNT 15

typedef enum s_err_code {
	ERR_SUCCESS = 0,
	ERR_GENERAL = 1,
	ERR_SYNTAX = 301,
	ERR_NO_FILE = 302,
	ERR_NO_VAR = 303,
	ERR_MALLOC = 304,
	ERR_FORK = 305,
	ERR_PIPE = 306,
	ERR_ARGS = 307,
	ERR_NO_CMD = 308,
	ERR_IS_FOLDER = 309,
	ERR_PERM = 310,
	ERR_IDENT = 311,
	ERR_IS_NO_FOLDER = 312,
	ERR_MANY_ARGS = 101,
	ERR_NUM_ARGS = 102,
	ERR_SIGINT = 130,
	ERR_SIGTER = 131,
}	t_err_code;

# define BI_COUNT 8

typedef enum s_buildin {
	BI_NULL = -1,
	BI_ECHO = 0,
	BI_CD = 1,
	BI_PWD = 2,
	BI_EXPORT = 3,
	BI_UNSET = 4,
	BI_ENV = 5,
	BI_EXIT = 6,
}	t_buildin;
#endif
