/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   num_free_all.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:27 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:27 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	num_free_all(t_num *head)
{
	t_num	*num;
	t_num	*tmp;

	num = head;
	while (num)
	{
		tmp = num;
		num = num->next;
		free(tmp);
	}
}
