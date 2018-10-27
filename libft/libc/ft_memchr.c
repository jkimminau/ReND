/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 21:14:35 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/24 21:42:08 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *tmp;
	unsigned char t;

	tmp = (unsigned char*)s;
	t = (unsigned char)c;
	while (n--)
	{
		if (*tmp == t)
			return (tmp);
		s++;
		tmp++;
	}
	return (NULL);
}
