/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:18:20 by jkimmina          #+#    #+#             */
/*   Updated: 2018/05/05 17:54:05 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_conv.h>
#include <stdio.h>

int		convert(va_list *ap, t_flags *flags)
{
	char	c;

	c = *flags->key;
	if (c == '%')
		return (conv_perc(flags));
	else if (c == 'p')
		return (conv_ptr(ap, flags));
	else if (ft_strchr("oO", c))
		return (conv_octal(c, ap, flags));
	else if (ft_strchr("xX", c))
		return (conv_hex(c, ap, flags));
	else if (ft_strchr("diD", c))
		return (conv_int(c, ap, flags));
	else if (ft_strchr("uU", c))
		return (conv_uint(c, ap, flags));
	else if (ft_strchr("cC", c))
		return (conv_char(ap, flags));
	else if (ft_strchr("sS", c))
		return (conv_str(ap, flags));
	return (0);
}
