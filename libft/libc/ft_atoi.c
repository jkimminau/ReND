/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:14:56 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/25 03:34:27 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_atoi(const char *str)
{
	unsigned long long	num;
	int					sign;

	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\f'
			|| *str == '\r' || *str == '\n' || *str == '\f')
		str++;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += (*str++ - '0');
		if (num > 9223372036854775807 && sign == 1)
			return (-1);
		if (num > 9223372036854775807 && sign == -1)
			return (0);
	}
	return (sign * num);
}
