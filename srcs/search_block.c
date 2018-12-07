/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:49:37 by heynard           #+#    #+#             */
/*   Updated: 2018/12/07 10:31:37 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_block	*search_ptr_in_area(t_area *list, void *ptr)
{
	t_block	*block;

	block = list->head;
	while (block)
	{
		if (block->data == ptr && !block->available)
			return (block);
		block = block->next;
	}
	return (NULL);
}

static t_block	*search_free_block_in_area(t_area *list, size_t size)
{
	t_block *tmp;

	tmp = list->head;
	while (tmp && (!tmp->available || tmp->size < size))
		tmp = tmp->next;
	return (tmp);
}

t_block			*search_ptr(void *ptr, t_area **list)
{
	t_block	*search;

	search = NULL;
	while (*list)
	{
		if ((search = search_ptr_in_area(*list, ptr)))
			break ;
		*list = (*list)->next;
	}
	return (search);
}

void			*search_free_block(int format, size_t size)
{
	t_area	*list;
	t_block	*search;
	size_t	old_size;

	list = fetch_first_area(NULL, GET);
	search = NULL;
	while (list)
	{
		if (list->format == format)
			if ((search = search_free_block_in_area(list, size)))
				break ;
		list = list->next;
	}
	if (search)
	{
		old_size = search->size;
		set_block(search, size, FALSE);
		if (old_size - search->size > align_16(sizeof(t_block)))
			split_block(search, old_size
					- search->size - align_16(sizeof(t_block)));
		return (search->data);
	}
	else
		return (create_area(format, size));
}
