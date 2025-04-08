/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CONSTANTS.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:47:17 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/03 13:20:28 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define ROOT_PROMPT_BLUE "\x1b[1;34mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_VIOLET "\x1b[1;95mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_PINK "\x1b[1;38;2;255;20;147mmini\x1b[0m🐚: \x1b[1m"

# define ERR_SYNTHAX_MSG "Found syntax error"
# define ERR_NO_FILE_MSG  "No such file or directroy"
# define ERR_NO_VAR_MSG  "No such variable"
# define ERR_MALLOC_MSG "Cannot allocate memory"
# define ERR_FORK_MSG "Cannot fork a process"
# define ERR_PIPE_MSG "Pipe failed"

# define ERR_COUNT 6

typedef enum s_err_code {
	ERR_SUCCESS = 0,
	ERR_SYNTAX = 301,
	ERR_NO_FILE = 302,
	ERR_NO_VAR = 303,
	ERR_MALLOC = 304,
	ERR_FORK = 305,
	ERR_PIPE = 306,
}	t_err_code;

#endif
