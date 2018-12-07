/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:10:07 by heynard           #+#    #+#             */
/*   Updated: 2018/12/05 18:09:58 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	attach_next(t_block *block)
{
	block->size = block->size + block->next->size
				+ align_16(sizeof(t_block));
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
}

static void	combine_free_blocks(t_block *block)
{
	if (block->prev && block->prev->available)
	{
		block = block->prev;
		attach_next(block);
	}
	if (block->next && block->next->available)
		attach_next(block);
}

void		free(void *ptr)
{
	t_block	*block;
	t_area	*p;

	if (!ptr)
		return ;
	p = fetch_first_area(NULL, GET);
	if ((block = search_ptr(ptr, &p)))
	{
		block->available = TRUE;
		combine_free_blocks(block);
	}
	else
		return ;
	if (p->head->available && !p->head->next)
		del_area(p);
}
