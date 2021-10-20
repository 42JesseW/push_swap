/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort_prerotate.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:08:54 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:08:57 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

char	*sort_prerotate_get_op(t_num *stack, char ab, bool asc)
{
	t_num	*num;
	int		len;
	char	*op;
	int		count;

	count = 1;
	num = stack;
	len = num_len(stack);
	op = ins_get_stack_op(ab, ROTATE);
	while (num)
	{
		if (!num->next)
			break ;
		if (count >= (len * 0.5))
		{
			op = ins_get_stack_op(ab, REVERSE_ROTATE);
			break ;
		}
		if ((asc && num->num > num->next->num)
			|| (!asc && num->num < num->next->num))
			break ;
		num = num->next;
		count++;
	}
	return (op);
}

/*
**
** DESCRIPTION:
**  - Rotate the stack most efficiently so its
**	  sorted in either ascending or descending order.
**	  Uses {sort_prerotate_get_op} to get the most
**	  efficient rotation operation. It then rotates
**	  until perfectly sorted.
**
**	All four pointers are needed for {ins_exec} but
**	the function actually operates on either stack
**	A or B. Which stack is used can be set using {c}.
**	{c - 97} then picks the right stack from {ab}.
*/
void	sort_prerotate(t_num **ab, char c, bool asc, bool write_stdout)
{
	int		idx;
	char	*op;

	if (!ab || (c != 'a' && c != 'b'))
		return ;
	idx = c - 97;
	if (!ab[idx])
		return ;
	op = sort_prerotate_get_op(ab[idx], c, asc);
	while (true)
	{
		if (asc && ab[idx]->num < ab[idx + 2]->num)
			break ;
		if (!asc && ab[idx]->num > ab[idx + 2]->num)
			break ;
		ins_exec(op, ab, write_stdout);
	}
}
