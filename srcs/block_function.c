/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:31:29 by heynard           #+#    #+#             */
/*   Updated: 2018/12/05 19:24:59 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	connect_block(t_block *block, t_block *prev, t_block *next)
{
	block->next = next;
	block->prev = prev;
	if (next)
		next->prev = block;
	if (prev)
		prev->next = block;
}

void	set_block(t_block *block, size_t size, int available)
{
	block->size = size;
	block->available = available;
	block->data = (void *)block + align_16(sizeof(t_block));
}

void	split_block(t_block *block, size_t size)
{
	t_block	*new_block;
	t_block	*next;

	if (size <= align_16(sizeof(t_block)))
		return ;
	new_block = (t_block *)(block->data + block->size);
	set_block(new_block, size, TRUE);
	next = (block->next) ? block->next : NULL;
	connect_block(new_block, block, next);
}
