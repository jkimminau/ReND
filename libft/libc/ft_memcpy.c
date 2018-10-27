/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:15:57 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/25 00:10:05 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dtmp;
	char		*stmp;
	size_t		i;

	dtmp = (char *)dst;
	stmp = (char *)src;
	i = -1;
	while (++i < n)
		*(dtmp + i) = *(stmp + i);
	return (dst);
}
