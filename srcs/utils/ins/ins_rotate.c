/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_rotate.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:47 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:47 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** rotate a - shift up all elements
** of stack a by 1. The first element
** becomes the last one.
*/

void	ins_rotatea(t_num **head)
{
	t_num	*num;
	t_num	*tmp;

	if (head[0] && head[0]->next)
	{
		tmp = head[0]->next;
		tmp->prev = NULL;
		num = head[0];
		while (num->next)
			num = num->next;
		num->next = head[0];
		head[0]->prev = num;
		head[0]->next = NULL;
		head[2] = head[0];
		head[0] = tmp;
	}
}

/*
** rotate b - shift up all elements
** of stack b by 1. The first element
** becomes the last one.
*/

void	ins_rotateb(t_num **head)
{
	t_num	*num;
	t_num	*tmp;

	if (head[1] && head[1]->next)
	{
		tmp = head[1]->next;
		tmp->prev = NULL;
		num = head[1];
		while (num->next)
			num = num->next;
		num->next = head[1];
		head[1]->prev = num;
		head[1]->next = NULL;
		head[3] = head[1];
		head[1] = tmp;
	}
}

void	ins_rotate_both(t_num **head)
{
	ins_rotatea(head);
	ins_rotateb(head);
}
