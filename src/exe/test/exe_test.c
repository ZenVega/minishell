/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:01:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:07:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "exe_test.h"

int	main(int argc, char **argv, char *envp[])
{
	t_app	*app;

	app = init_shell(envp);
	ft_printf("RUNNING EXE TESTS\n");
	char		*test_1_args[] = {"pwd", NULL};
	t_cmd_info	test_1 = {0, 1, test_1_args, BIN};

	char		*test_2_args[] = {"unknown", NULL};
	t_cmd_info	test_2 = {0, 1, test_2_args, BIN};

	ft_printf("Test 1: pwd, stdout\n");
	exe(app, &test_1);
	ft_printf("Test 2: unknown, stdout\n");
	exe(app, &test_2);
	while (0)
		argv[argc] = 0;
	free_malloc_list(app);
}
