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

int main(int argc, char **argv, char *envp[]) {
	t_app *app = init_shell(envp);
	ft_printf("RUNNING EXE TESTS\n");

	// Test 1: "pwd"
	char *test_args_1[] = {"pwd", NULL};
	t_cmd_info test_1 = {0, 1, test_args_1, BIN};

	// Test 2: "unknown"
	char *test_args_2[] = {"unknown", NULL};
	t_cmd_info test_2 = {0, 1, test_args_2, BIN};

	// Test 3: "ls" with output to file
	int fd_out = open("test_out", O_RDWR | O_CREAT, 0644);
	if (fd_out == -1) {
		perror("Error opening test_out");
		free_malloc_list(app);
		return 1;
	}

	char *test_args_3[] = {"ls", NULL};
	t_cmd_info test_3 = {0, fd_out, test_args_3, BIN};

	// Test 4: "sort" with infile
	int fd_in = open("test_in", O_RDONLY, 0644);
	if (fd_in == -1) {
		perror("Error opening test_in");
		free_malloc_list(app);
		return 1;
	}

	char *test_args_4[] = {"sort", NULL};
	t_cmd_info test_4 = {fd_in, 1, test_args_4, BIN};

	// Execute tests
	ft_printf("\nTest 1: pwd, stdout\n");
	exe(app, &test_1);

	ft_printf("\nTest 2: unknown, stdout\n");
	exe(app, &test_2);

	ft_printf("\nTest 3: ls, test_out\n");
	exe(app, &test_3);
	close(fd_out);
	ft_printf("\nTest 4: ls, test_in\n");
	exe(app, &test_4);
	close(fd_in);

	// Cleanup
	free_malloc_list(app);
	while (0)
		argv[argc] = 0;

	return 0;
}
