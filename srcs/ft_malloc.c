/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:15:52 by heynard           #+#    #+#             */
/*   Updated: 2018/12/07 10:30:48 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		get_format(size_t size)
{
	if (size <= TINY_N)
		return (TINY);
	if (size <= SMALL_M)
		return (SMALL);
	return (LARGE);
}

void	*valloc(size_t size)
{
	void	*ptr;
	int		format;

	size = align_area(LARGE, size);
	format = get_format(size);
	if (!area || format == LARGE)
		return (create_area(format, size));
	ptr = search_free_block(format, size);
	return (ptr);
}

void	*calloc(size_t count, size_t size)
{
	size_t	full_size;
	void	*new_alloc;

	full_size = count * size;
	new_alloc = malloc(full_size);
	if (full_size)
		ft_bzero(new_alloc, full_size);
	return (new_alloc);
}

void	*malloc(size_t size)
{
	void	*ptr;
	int		format;

	size = align_16(size);
	format = get_format(size);
	if (!area || format == LARGE)
		return (create_area(format, size));
	ptr = search_free_block(format, size);
	return (ptr);
}
