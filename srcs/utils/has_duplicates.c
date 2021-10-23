/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   has_duplicates.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:08:42 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:43 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** has_duplicates() checks if no duplicate
** numbers have been passed to main(). It
** also sets the numbers in their corresponding
** order in the newly allocated stack and checks
** if INT_MIN < n < INT_MAX.
**
**	@PARAM {int*}	stack
**	@PARAM {int}	argc
**	@PARAM {char**}	argv
**	@RETURN {bool}
*/

bool	has_duplicates(int *nums, int argc, char **argv)
{
	int		i;
	int		j;
	long	num;

	i = 0;
	while (i < argc)
	{
		num = ft_atol(argv[i]);
		if (num < INT_MIN || num > INT_MAX)
			return (true);
		if (i != 0)
		{
			j = 0;
			while (j < i)
			{
				if (nums[j] == num)
					return (true);
				j++;
			}
		}
		nums[i] = (int)num;
		i++;
	}
	return (false);
}
