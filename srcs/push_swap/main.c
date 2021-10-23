/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:13 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:14 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	exit_push_swap(t_num **ab, int *nums, bool err)
{
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (err)
	{
		write(STDERR_FILENO, "Error\n", 7);
		exit_code = EXIT_FAILURE;
	}
	if (nums)
		free(nums);
	if (ab[1])
	{
		num_free_all(ab[1]);
		num_free_all(ab[0]);
	}
	exit(exit_code);
}

int	main(int argc, char *argv[])
{
	t_num	*ab[4];
	int		*nums;

	ab[1] = NULL;
	if (argc < 2 || !valid_digits(argc, argv))
		exit_push_swap(ab, NULL, (argc >= 2));
	nums = malloc((argc - 1) * sizeof(int));
	if (!nums || has_duplicates(nums, argc - 1, argv + 1))
		exit_push_swap(ab, nums, true);
	if (!load_stack(ab, nums, argc - 1))
		exit_push_swap(ab, nums, true);
	init_stack_ptr(ab);
	push_swap(ab, true);
	num_free_all(ab[0]);
	free(nums);
	return (0);
}
