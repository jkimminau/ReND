/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:32:35 by jkimmina          #+#    #+#             */
/*   Updated: 2018/07/23 15:34:59 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_CONV_H
# define FT_PRINTF_CONV_H

# include <stdarg.h>
# include "../libft.h"
# include "./ft_printf_flags.h"
# include "./ft_printf_struct.h"

intmax_t	conv_signed(va_list *ap, t_flags *flags);
uintmax_t	conv_unsigned(va_list *ap, t_flags *flags);
int			conv_perc(t_flags *flags);
int			conv_ptr(va_list *ap, t_flags *flags);
int			conv_octal(char k, va_list *ap, t_flags *flags);
int			conv_int(char k, va_list *ap, t_flags *flags);
int			conv_uint(char k, va_list *ap, t_flags *flags);
int			conv_hex(char k, va_list *ap, t_flags *flags);
int			conv_str(va_list *ap, t_flags *flags);
int			conv_char(va_list *ap, t_flags *flags);
int			convert(va_list *ap, t_flags *flags);

#endif
