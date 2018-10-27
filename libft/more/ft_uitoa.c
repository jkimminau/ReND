/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 22:03:24 by jkimmina          #+#    #+#             */
/*   Updated: 2018/04/28 22:33:38 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_uitoa(uintmax_t n)
{
	char			*str;
	unsigned int	size;
	uintmax_t		num;

	size = 1;
	num = n;
	while (num >= 10)
	{
		size++;
		num /= 10;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
	{
		str[size] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}
