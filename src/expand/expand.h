/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:53:32 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 11:49:50 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../error/error.h"
# include "../includes/types.h"
# include "../libft/libft.h"
# include "../utils/utils.h"
# include "../parser/parser.h"

//expand.c
void	expand(t_parser_info *p_info, t_app *app, t_cmd_info *cmd);

//expand_utils.c
int		replace_return(t_app *app, t_parser_info *p_info, int i_dol);
int		replace_var(t_app *app, t_parser_info *p_info, char *p_dol);

#endif
