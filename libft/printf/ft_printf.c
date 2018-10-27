/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:48:25 by jkimmina          #+#    #+#             */
/*   Updated: 2018/06/05 12:13:06 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

t_flags	*add_option(t_flags *flags, char **str)
{
	if (**str == '#')
		flags->alt = (*(*str)++ == '#');
	else if (**str == '0')
		flags->zero = (*(*str)++ == '0');
	else if (**str == '-')
		flags->minus = (*(*str)++ == '-');
	else if (**str == '+')
		flags->plus = (*(*str)++ == '+');
	else if (**str == ' ')
		flags->space = (*(*str)++ == ' ');
	else if (**str >= '0' && **str <= '9')
	{
		flags->width = ft_atoi((*str));
		while (**str >= '0' && **str <= '9')
			(*str)++;
	}
	else if (**str == '.')
	{
		flags->prec = ft_atoi(++(*str));
		while (**str >= '0' && **str <= '9')
			(*str)++;
	}
	else
		return (free_flags(flags));
	return (flags);
}

t_flags	*read_flags(char **str)
{
	int		i;
	t_flags	*flags;

	flags = new_flags();
	while (ft_strchr("hljzsSpdDioOuUxXcC%", **str) == 0 && **str != '\0')
		if ((flags = add_option(flags, str)) == 0)
			return (0);
	i = 0;
	while (ft_strchr("sSpdiDoOuUxXcC%", *(*str + i)) == 0
			&& **str != '\0')
		i++;
	flags->flagstr = ft_strsub(*str, 0, i);
	flags->key = ft_strdup((*str) + i);
	*str += i;
	if (**str == '\0')
		return (free_flags(flags));
	return (flags);
}

int		handle_conversion(char **str, va_list *ap)
{
	t_flags	*flags;
	int		ret;

	(*str)++;
	if (*str == 0 || (flags = read_flags(str)) == 0)
		return (0);
	ret = convert(ap, flags);
	(*str)++;
	free_flags(flags);
	return (ret);
}

int		ft_printf(char *str, ...)
{
	va_list ap;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			write(1, str, i);
			str += i;
			i = 0;
			len += handle_conversion(&str, &ap);
		}
		else
		{
			len++;
			i++;
		}
	}
	write(1, str, i);
	va_end(ap);
	return (len);
}
