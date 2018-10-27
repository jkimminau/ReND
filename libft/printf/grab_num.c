/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grab_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:01:49 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 04:08:52 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_conv.h>

intmax_t	conv_signed(va_list *ap, t_flags *flags)
{
	if (ft_strcmp(flags->flagstr, "hh") == 0)
		return ((signed char)va_arg(*ap, int));
	if (ft_strcmp(flags->flagstr, "h") == 0)
		return ((short)va_arg(*ap, int));
	if (ft_strcmp(flags->flagstr, "l") == 0)
		return (va_arg(*ap, long));
	if (ft_strcmp(flags->flagstr, "ll") == 0)
		return (va_arg(*ap, long long));
	if (ft_strcmp(flags->flagstr, "j") == 0)
		return (va_arg(*ap, intmax_t));
	if (ft_strcmp(flags->flagstr, "z") == 0)
		return (va_arg(*ap, size_t));
	return (va_arg(*ap, int));
}

uintmax_t	conv_unsigned(va_list *ap, t_flags *flags)
{
	uintmax_t	num;

	if (ft_strcmp(flags->flagstr, "hh") == 0)
		num = ((unsigned char)va_arg(*ap, int));
	else if (ft_strcmp(flags->flagstr, "h") == 0)
		num = ((unsigned short)va_arg(*ap, int));
	else if (ft_strcmp(flags->flagstr, "l") == 0)
		num = va_arg(*ap, unsigned long);
	else if (ft_strcmp(flags->flagstr, "ll") == 0)
		num = va_arg(*ap, unsigned long long);
	else if (ft_strcmp(flags->flagstr, "j") == 0)
		num = va_arg(*ap, uintmax_t);
	else if (ft_strcmp(flags->flagstr, "z") == 0)
		num = va_arg(*ap, size_t);
	else
		num = va_arg(*ap, unsigned int);
	return (num);
}
