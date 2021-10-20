/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_stack_ptr.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:10:21 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:10:21 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

void	init_stack_ptr_set_rank(t_num **ab)
{
	t_num	*num;
	t_num	*tmp;
	int		rank;
	int		len;

	num = ab[0];
	len = num_len(ab[0]);
	while (num)
	{
		rank = len;
		tmp = ab[0];
		while (tmp)
		{
			if (tmp != num && num->num < tmp->num)
				rank--;
			tmp = tmp->next;
		}
		num->rank = rank;
		num = num->next;
	}
}

/*
** save pointers to the last
** numbers for performance.
*/

void	init_stack_ptr(t_num **ab)
{
	t_num	*num;

	ab[3] = NULL;
	num = ab[0];
	while (num->next)
		num = num->next;
	ab[2] = num;
	init_stack_ptr_set_rank(ab);
}
