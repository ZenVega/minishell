/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:27:02 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 17:33:38 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASK_H
# define MASK_H

# include "../error/error.h"
# include "../includes/types.h"
# include "../malloc_list/malloc_list.h"

//mask.c
int			create_mask(t_parser_info *p_info, t_list **malloc_list,
				t_cmd_info *cmd);

#endif
