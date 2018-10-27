/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 19:28:22 by jkimmina          #+#    #+#             */
/*   Updated: 2018/05/07 14:08:12 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf_conv.h>
#include <stdio.h>

int		conv_wchar(va_list *ap, t_flags *flags)
{
	wchar_t	ret;
	char	*tmp;
	int		len;

	len = 1;
	ret = va_arg(*ap, wchar_t);
	if (flags->width > 1)
	{
		len = flags->width;
		tmp = (char*)malloc(flags->width);
		ft_memset(tmp, ' ', flags->width - 1);
		tmp[flags->width - 1] = '\0';
		if (!flags->minus)
			ft_putstr(tmp);
		write(1, &ret, 1);
		if (flags->minus)
			ft_putstr(tmp);
		free(tmp);
	}
	else
		write(1, &ret, 1);
	return (len);
}

int		conv_char(va_list *ap, t_flags *flags)
{
	char	*ret;
	int		len;

	if (*flags->key == 'C' || ft_strcmp(flags->flagstr, "l") == 0)
		return (conv_wchar(ap, flags));
	len = 1;
	ret = ft_strnew(2);
	ret[0] = va_arg(*ap, int);
	if (*ret > 127)
		return (-1);
	if (ret[0] < 32 || ret[0] > 126)
		flags->strlen++;
	if (flags->width > 1)
	{
		ret = num_flag(ret, flags);
		len = flags->width;
	}
	write(1, ret, len);
	free(ret);
	return (len);
}

int		conv_wstr(va_list *ap, t_flags *flags)
{
	wchar_t	*ret;
	char	*tmp;
	int		len;

	ret = va_arg(*ap, wchar_t*);
	if (ret == 0)
		return (write(1, "(null)", 6));
	len = ft_wstrlen(ret);
	if (flags->width > len)
	{
		len = flags->width;
		tmp = (char*)malloc(flags->width);
		ft_memset(tmp, ' ', flags->width - len);
		tmp[flags->width - 1] = '\0';
		if (!flags->minus)
			ft_putstr(tmp);
		ft_putwstr(ret);
		if (flags->minus)
			ft_putstr(tmp);
		free(tmp);
	}
	else
		ft_putwstr(ret);
	return (len);
}

int		conv_str(va_list *ap, t_flags *flags)
{
	char	*ret;
	char	*tmp;
	int		len;

	if (*flags->key == 'S' || ft_strcmp(flags->flagstr, "l") == 0)
		return (conv_wstr(ap, flags));
	tmp = va_arg(*ap, char*);
	if (tmp == 0)
		return (write(1, "(null)", 6));
	if (flags->prec > -1)
		ret = ft_strsub(tmp, 0, flags->prec);
	else
		ret = ft_strdup(tmp);
	if (flags->width)
		ret = num_flag(ret, flags);
	len = ft_strlen(ret);
	write(1, ret, len);
	free(ret);
	return (len);
}
