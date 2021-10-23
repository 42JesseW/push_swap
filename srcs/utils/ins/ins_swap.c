/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_swap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:38 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:38 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** swap a - swap the first 2 elements at
** the top of stack a. Do nothing if there
** is only one or no elements).
*/

void	ins_swapa(t_num **head)
{
	t_num	*first;
	t_num	*second;

	if (head[0] && head[0]->next)
	{
		second = head[0];
		first = second->next;
		if (first == head[2])
			head[2] = second;
		if (first->next)
			first->next->prev = second;
		second->next = first->next;
		second->prev = first;
		first->prev = NULL;
		first->next = second;
		head[0] = first;
	}
}

/*
** swap b - swap the first 2 elements at
** the top of stack b. Do nothing if there
** is only one or no elements).
*/

void	ins_swapb(t_num **head)
{
	t_num	*first;
	t_num	*second;

	if (head[1] && head[1]->next)
	{
		second = head[1];
		first = second->next;
		if (first == head[3])
			head[3] = second;
		if (first->next)
			first->next->prev = second;
		second->next = first->next;
		second->prev = first;
		first->prev = NULL;
		first->next = second;
		head[1] = first;
	}
}

/*
** swap a and swap b at the same time
*/

void	ins_swap_both(t_num **head)
{
	ins_swapa(head);
	ins_swapb(head);
}
