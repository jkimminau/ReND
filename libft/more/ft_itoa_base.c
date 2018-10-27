/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:57:33 by jkimmina          #+#    #+#             */
/*   Updated: 2018/04/23 16:41:19 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	get_digit(int num)
{
	if (num < 10)
		return ('0' + num);
	else
		return ('a' + num - 10);
}

char	*ft_itoa_base(unsigned int n, int base)
{
	char			*str;
	unsigned int	size;
	unsigned int	num;

	num = n;
	size = 1;
	while (num >= (unsigned int)base)
	{
		size++;
		num /= base;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	num = n;
	while (size--)
	{
		str[size] = get_digit(num % base);
		num = num / base;
	}
	return (str);
}
