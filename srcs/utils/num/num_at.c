/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_at.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:30 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:31 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
** num_at() returns the index of
** {num} at index {idx} in {stack}.
**
** returns -1 if unable to look
** through stack for rank {rank}.
** If rank not found, return {num_len()}.
*/

int	num_at(t_num *stack, int rank)
{
	t_num	*num;
	int		idx;

	if (!stack || rank <= 0)
		return (-1);
	idx = 0;
	num = stack;
	while (num && num->rank != rank)
	{
		num = num->next;
		idx++;
	}
	return (idx);
}
