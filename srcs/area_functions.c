/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   area_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:25:18 by heynard           #+#    #+#             */
/*   Updated: 2018/12/05 18:11:00 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_area	*fetch_first_area(t_area *new_first, t_flag flag)
{
	static t_area	*first = NULL;

	if (new_first || flag == FORCE)
	{
		first = new_first;
		if (first)
			first->prev = NULL;
	}
	return (first);
}

void	del_area(t_area *p)
{
	if (!p->prev)
	{
		area = p->next;
		fetch_first_area(area, FORCE);
	}
	else if (!p->next)
		p->prev->next = NULL;
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	munmap(p, p->size);
}

void	goto_last_area(t_area **prev)
{
	if (!area)
		return ;
	while (area->next)
		area = area->next;
	*prev = area;
	area = area->next;
}

void	init_area(int format, size_t size, t_area *prev)
{
	area->format = format;
	area->size = size;
	area->head = (t_block *)((void *)area + align_16(sizeof(t_area)));
	area->prev = prev;
	if (prev)
		prev->next = area;
	area->next = NULL;
}

void	*create_area(int format, size_t size)
{
	size_t	area_size;
	size_t	new_block_size;
	t_area	*prev;

	area_size = align_area(format, size
				+ align_16(sizeof(t_area)) + align_16(sizeof(t_block)));
	area = fetch_first_area(NULL, GET);
	prev = NULL;
	goto_last_area(&prev);
	if (!(area = mmap(0, area_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANON, -1, 0)))
		return (NULL);
	init_area(format, area_size, prev);
	if (!prev)
		fetch_first_area(area, GET);
	set_block(area->head, size, FALSE);
	connect_block(area->head, NULL, NULL);
	new_block_size = area->size - (align_16(sizeof(t_area))
					+ align_16(sizeof(t_block)) * 2 + size);
	if (format != LARGE)
		split_block(area->head, new_block_size);
	return (area->head->data);
}
