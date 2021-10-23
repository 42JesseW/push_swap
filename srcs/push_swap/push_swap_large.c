/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap_large.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:07 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:08 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	push_swap_large_loop(t_num **ab, bool write_stdout,
								int max_bits, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < size)
		{
			if (((ab[0]->rank >> i) & 1) == 1)
				ins_exec(ROTATEA, ab, write_stdout);
			else
				ins_exec(PUSHB, ab, write_stdout);
			j++;
		}
		while (ab[1])
			ins_exec(PUSHA, ab, write_stdout);
		i++;
	}
}

/*
** push_swap_large() implements a binary
** radix sorting algorithm where the
** group sort subroutines are done using
** individual bits (since we have two stacks).
**
** [algorithm]
**	- Rank all numbers (init_stack_ptr_set_rank())
**	  This allows us to work with negative numbers and
**	  prevents us from doing extra work with very big
**	  numbers.
**	- Get the biggest rank and calculate how many bits
**	  are needed (i.e. how many group sort subroutines).
**	- [group sort]
**		- Loop over stack A and for each element check
**		  current bit value ((rank >> i) & 1). If 0, then
**		  push to B. Else rotate up to the next number.
**	  	- Push all numbers from B to stack A
*/

void	push_swap_large(t_num **ab, bool write_stdout)
{
	int	size;
	int	max_num;
	int	max_bits;

	max_bits = 0;
	size = num_len(ab[0]);
	max_num = size - 1;
	while ((max_num >> max_bits) != 0)
		max_bits++;
	push_swap_large_loop(ab, write_stdout, max_bits, size);
}
