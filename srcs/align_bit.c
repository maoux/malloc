/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align_bit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:29:21 by heynard           #+#    #+#             */
/*   Updated: 2018/12/07 10:29:52 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		log_area(size_t n)
{
	int	cnt;

	cnt = 0;
	while (n > 8)
	{
		n >>= 4;
		cnt += 4;
	}
	while (n != 1)
	{
		n >>= 1;
		cnt++;
	}
	return (cnt);
}

size_t			align_area(const int format, const size_t size)
{
	int		log;
	size_t	area_size;

	if (format == TINY)
		area_size = 4 * getpagesize();
	else if (format == SMALL)
		area_size = 32 * getpagesize();
	else
		area_size = getpagesize();
	log = log_area(area_size);
	return ((((size - 1) >> log) << log) + area_size);
}

/*
** opération d'alignement : size devient le prochain multiple de 16 bits
** alignement indispensable pour vim
** >> 4 --> division par 16
** << 4 --> multiplication par 16 ( multiple de 16 < size - 1)
** + 16 --> dépasse l'ancienne valeur ( multiple de 16 > size + 1)
*/

size_t			align_16(const size_t size)
{
	if (!size)
		return (16);
	return ((((size - 1) >> 4) << 4) + 16);
}
