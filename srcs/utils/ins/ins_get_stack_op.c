/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ins_get_stack_op.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jevan-de <jevan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 14:09:53 by jevan-de      #+#    #+#                 */
/*   Updated: 2021/10/17 14:09:53 by jevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

static struct s_ins	g_instruction_map[] = {
	{SWAP, 'a', SWAPA},
	{SWAP, 'b', SWAPB},
	{SWAP, 'c', SWAP_BOTH},
	{PUSH, 'a', PUSHA},
	{PUSH, 'b', PUSHB},
	{ROTATE, 'a', ROTATEA},
	{ROTATE, 'b', ROTATEB},
	{ROTATE, 'c', ROTATE_BOTH},
	{REVERSE_ROTATE, 'a', REVERSE_ROTATEA},
	{REVERSE_ROTATE, 'b', REVERSE_ROTATEB},
	{REVERSE_ROTATE, 'c', REVERSE_ROTATE_BOTH},
	{0, 0, NULL}
};

char	*ins_get_stack_op(char ab, enum e_ins ins)
{
	struct s_ins	ins_map;
	int				idx;

	idx = 0;
	while (g_instruction_map[idx].op)
	{
		ins_map = g_instruction_map[idx];
		if (ins_map.ins == ins && ins_map.abc == ab)
			return (ins_map.op);
		idx++;
	}
	return (NULL);
}
