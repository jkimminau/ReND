/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:00:34 by jkimmina          #+#    #+#             */
/*   Updated: 2018/07/23 15:35:10 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FLAGS_H
# define FT_PRINTF_FLAGS_H

# include "../libft.h"
# include "./ft_printf_struct.h"

char	*alt_flag(char *conv, t_flags *flags);
char	*space_flag(char *conv, t_flags *flags);
char	*prec_flag(char *conv, t_flags *flags);
char	*num_flag(char *conv, t_flags *flags);

#endif
