/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:41:55 by jkimmina          #+#    #+#             */
/*   Updated: 2018/04/29 14:20:07 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_struct.h>

t_flags		*free_flags(t_flags *flags)
{
	if (flags->flagstr != 0)
		free(flags->flagstr);
	if (flags->key != 0)
		free(flags->key);
	free(flags);
	flags = 0;
	return (flags);
}

t_flags		*new_flags(void)
{
	t_flags		*flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->alt = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->prec = -1;
	flags->width = 0;
	flags->strlen = 0;
	flags->flagstr = 0;
	flags->key = 0;
	return (flags);
}
