/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   push_swap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:01 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:02 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
**
**	DESCRIPTION:
**	 - This functions takes an array of 4 pointers as its input.
**	   The first pointer points to the first node in Stack A. The
**	   second pointer points to the first node in Stack B. The third
**	   pointer points to the last node in Stack A. The fourth pointer
**	   points to the last node in Stack B.
**
**	   As its output, this functions writes to STDOUT the instructions
**	   needed to sort Stack A. Instructions are as follows:
**
**		# define SWAPA "sa"
**		# define SWAPB "sb"
**		# define SWAP_BOTH "ss"
**		# define PUSHA "pa"
**		# define PUSHB "pb"
**		# define ROTATEA "ra"
**		# define ROTATEB "rb"
**		# define ROTATE_BOTH "rr"
**		# define REVERSE_ROTATEA "rra"
**		# define REVERSE_ROTATEB "rrb"
**		# define REVERSE_ROTATE_BOTH "rrr"
**
**	 - Constraints:
**	   This function assumes that at least one node is located in stack
**	   A and that Stack B and the pointer pointing to the last node in
**	   stack B are NULL. There may be no duplicate numbers and they may
**	   not be bigger than {INT_MAX} or smaller than {INT_MIN}.
**
**	@PARAM {t_num**}	ab
**	@RETURN {void}
**
*/

void	push_swap(t_num *ab[4], bool write_stdout)
{
	if (is_sorted(ab[0], CHECK_ALL, true, true) && !ab[1])
		return ;
	if (num_len(ab[0]) <= 5)
		push_swap_small(ab, write_stdout);
	else
		push_swap_large(ab, write_stdout);
}
