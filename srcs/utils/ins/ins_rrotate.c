/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_rrotate.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:44 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:44 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** reverse rotate a - shift down all
** elements of stack a by 1. The last
** element becomes the first one.
*/

void	ins_rrotatea(t_num **head)
{
	t_num	*num;

	if (head[0] && head[0]->next)
	{
		num = head[0];
		while (num->next)
			num = num->next;
		head[0]->prev = num;
		num->next = head[0];
		num->prev->next = NULL;
		head[2] = num->prev;
		num->prev = NULL;
		head[0] = num;
	}
}

/*
** reverse rotate b - shift down all
** elements of stack b by 1. The last
** element becomes the first one.
*/

void	ins_rrotateb(t_num **head)
{
	t_num	*num;

	if (head[1] && head[1]->next)
	{
		num = head[1];
		while (num->next)
			num = num->next;
		head[1]->prev = num;
		num->next = head[1];
		num->prev->next = NULL;
		head[3] = num->prev;
		num->prev = NULL;
		head[1] = num;
	}
}

void	ins_rrotate_both(t_num **head)
{
	ins_rrotatea(head);
	ins_rrotateb(head);
}
