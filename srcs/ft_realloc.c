/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:11:32 by heynard           #+#    #+#             */
/*   Updated: 2018/12/05 18:10:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*reallocate(t_block *block, size_t size)
{
	void	*new_alloc;

	if (!(new_alloc = malloc(size)))
		return (NULL);
	if (block)
	{
		ft_memcpy(new_alloc, block->data, block->size);
		free(block->data);
	}
	return (new_alloc);
}

void	*extend_block(t_block *block, size_t size)
{
	size_t full_size;

	if (!block->next || !block->next->available ||
			(block->size + block->next->size
			+ align_16(sizeof(t_block)) < size))
		return (NULL);
	full_size = block->size + block->next->size + align_16(sizeof(t_block));
	block->next = block->next->next;
	set_block(block, size, FALSE);
	if (full_size - size > align_16(sizeof(t_block)))
		split_block(block, full_size - size - align_16(sizeof(t_block)));
	return (block->data);
}

t_block	*reduce_block(t_block *block, size_t size)
{
	size_t old_size;

	old_size = block->size;
	if (old_size - size > align_16(sizeof(t_block)))
	{
		block->size = size;
		split_block(block, old_size - size - align_16(sizeof(t_block)));
	}
	return (block->data);
}

void	*reallocf(void *ptr, size_t size)
{
	void *new_alloc;

	new_alloc = realloc(ptr, size);
	if (!new_alloc)
		free(ptr);
	return (new_alloc);
}

void	*realloc(void *ptr, size_t size)
{
	t_block *block;
	t_area	*p;

	size = align_16(size);
	if (!ptr || !size)
		return (reallocate(ptr, size));
	p = fetch_first_area(NULL, GET);
	if (!(block = search_ptr(ptr, &p)))
		return (reallocate(NULL, size));
	if (block->size > size)
		ptr = reduce_block(block, size);
	else
	{
		if (block->size != size && !(ptr = extend_block(block, size)))
			return (reallocate(block, size));
	}
	return (ptr);
}
