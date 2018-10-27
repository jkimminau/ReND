/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:05:20 by jkimmina          #+#    #+#             */
/*   Updated: 2018/07/23 15:35:17 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_STRUCT_H
# define FT_PRINTF_STRUCT_H

# include <stdlib.h>

typedef struct	s_flags
{
	int			alt;
	int			zero;
	int			minus;
	int			plus;
	int			space;
	int			prec;
	int			width;
	int			strlen;
	char		*key;
	char		*flagstr;
}				t_flags;

t_flags			*free_flags(t_flags *flags);
t_flags			*new_flags(void);

#endif
