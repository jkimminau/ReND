/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:29:05 by jkimmina          #+#    #+#             */
/*   Updated: 2018/09/09 03:51:12 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_conv.h>
#include <ft_printf_flags.h>
#include <stdio.h>

int			conv_octal(char k, va_list *ap, t_flags *flags)
{
	char		*res;
	int			len;
	uintmax_t	num;

	if (k == 'O')
		num = va_arg(*ap, unsigned long);
	else
		num = conv_unsigned(ap, flags);
	res = ft_uitoa_base(num, 8);
	if (flags->prec > -1)
		res = prec_flag(res, flags);
	if (flags->alt && num > 0)
		res = ft_strjoin("0", res);
	if (flags->width > 0)
		res = num_flag(res, flags);
	len = ft_strlen(res);
	write(1, res, len);
	free(res);
	return (len);
}

int			conv_int(char k, va_list *ap, t_flags *flags)
{
	char		*res;
	int			len;
	intmax_t	num;

	if (k == 'D')
		num = va_arg(*ap, long);
	else
		num = conv_signed(ap, flags);
	res = ft_sitoa(num);
	if (flags->prec > -1)
		res = prec_flag(res, flags);
	if (flags->plus && ft_strchr(res, '-') == 0)
		res = ft_addprefix("+", res);
	if (flags->space)
		res = space_flag(res, flags);
	if (flags->width > 0)
		res = num_flag(res, flags);
	len = ft_strlen(res);
	write(1, res, len);
	free(res);
	return (len);
}

int			conv_uint(char k, va_list *ap, t_flags *flags)
{
	char		*res;
	int			len;
	intmax_t	num;

	if (k == 'U')
		num = va_arg(*ap, unsigned long);
	else
		num = conv_unsigned(ap, flags);
	res = ft_uitoa(num);
	if (flags->prec > -1)
		res = prec_flag(res, flags);
	if (flags->width > 0)
		res = num_flag(res, flags);
	len = ft_strlen(res);
	write(1, res, len);
	free(res);
	return (len);
}

int			conv_hex(char k, va_list *ap, t_flags *flags)
{
	char		*res;
	int			len;
	uintmax_t	num;

	num = conv_unsigned(ap, flags);
	res = ft_uitoa_base(num, 16);
	if (flags->prec > -1)
		res = prec_flag(res, flags);
	if (flags->alt && num > 0)
		res = ft_addprefix("0x", res);
	if (k == 'X')
		res = ft_capitalize(res);
	if (flags->width > 0)
		res = num_flag(res, flags);
	len = ft_strlen(res);
	write(1, res, len);
	free(res);
	return (len);
}
