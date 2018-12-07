/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 06:38:47 by heynard           #+#    #+#             */
/*   Updated: 2018/12/05 19:44:37 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_area_allocs(t_block *b, size_t *size)
{
	while (b)
	{
		if (b->available == FALSE)
		{
			ft_printf("%p - %p : %d octets\n",
						b->data, (void *)(b->data + b->size), b->size);
			*size += b->size;
		}
		b = b->next;
	}
}

void	print_allocs(t_area *area_list, size_t *size)
{
	if (area_list->format == TINY)
		ft_putstr("TINY : ");
	else if (area_list->format == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_printf("%p\n", area_list);
	print_area_allocs(area_list->head, size);
}

void	show_alloc_mem(void)
{
	t_area	*area_list;
	size_t	total;

	total = 0;
	if (!(area_list = fetch_first_area(NULL, GET)))
		return ;
	while (area_list)
	{
		print_allocs(area_list, &total);
		area_list = area_list->next;
	}
	ft_printf("Total : %zd octets\n", total);
}
