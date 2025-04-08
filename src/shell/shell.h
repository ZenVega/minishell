/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:40:03 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 15:29:50 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../buildins/pwd/pwd.h"
# include "../exe/exe.h"
# include "../includes/types.h"
# include "../includes/CONSTANTS.h"
# include "../libft/libft.h"
# include "../malloc_list/malloc_list.h"
# include "../parser/parser.h"

void	start_shell(t_app *app);

#endif
