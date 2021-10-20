/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_digits.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:07:24 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:19 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** valid_digits() checks wether the arguments
** passed to main() are propper integers i.e.
** can only contain a - at index 0 and further
** only consist of ASCII digits.
*/

bool	valid_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = argc - 1;
	while (i)
	{
		j = 0;
		if (!(*argv[i]))
			return (false);
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				if (j == 0 && argv[i][j] != '-')
					return (false);
				if (j > 0 && !ft_isdigit(argv[i][j]))
					return (false);
			}
			j++;
		}
		i--;
	}
	return (true);
}
