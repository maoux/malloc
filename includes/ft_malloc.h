/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:36:43 by heynard           #+#    #+#             */
/*   Updated: 2018/12/07 10:34:35 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/includes/libft.h"
# include <sys/mman.h>
# include <unistd.h>

# define TINY_N 	128
# define SMALL_M	1024

# define TRUE		1
# define FALSE		0

typedef enum		e_type_format
{
	TINY,
	SMALL,
	LARGE
}					t_type_format;

typedef enum		e_flag
{
	FORCE,
	GET
}					t_flag;

typedef struct		s_block
{
	int				available;
	size_t			size;
	void			*data;
	struct s_block	*prev;
	struct s_block	*next;
}					t_block;

typedef struct		s_area
{
	int				format;
	size_t			size;
	t_block			*head;
	struct s_area	*prev;
	struct s_area	*next;
}					t_area;

struct s_area		*area;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				*calloc(size_t count, size_t size);
void				*valloc(size_t size);

size_t				align_area(const int format, const size_t size);
size_t				align_16(const size_t size);

void				*create_area(int format, size_t size);
t_area				*fetch_first_area(t_area *first_area, t_flag flag);
void				del_area(t_area *area);

void				*search_free_block(int format, size_t size);
t_block				*search_ptr(void *ptr, t_area **p);

void				set_block(t_block *block, size_t size, int free);
void				connect_block(t_block *block, t_block *prev, t_block *next);
void				split_block(t_block *block, size_t size);

#endif
