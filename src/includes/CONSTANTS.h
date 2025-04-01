/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CONSTANTS.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:47:17 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/25 15:16:38 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define ROOT_PROMPT_BLUE "\x1b[1;34mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_VIOLET "\x1b[1;95mmini🐚:\x1b[0m \x1b[1m"
# define ROOT_PROMPT_PINK "\x1b[1;38;2;255;20;147mmini\x1b[0m🐚: \x1b[1m"

typedef enum s_error_code {
	ERR_SUCCESS = 0,
	ERR_SYNTAX = 301,
	ERR_FILE_NOT_FOUND = 302,
}	t_error_code;

# define ERR_SUCCESS "Exit without error"
# define ERR_SYNTHAX_MSG "Found syntax error"
# define ERR_FILE_NOT_FOUND_MSG  "No such file or directroy"
#endif
