/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:32:28 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/25 00:13:09 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dtmp;
	const unsigned char	*stmp;

	dtmp = (unsigned char *)dst;
	stmp = (const unsigned char *)src;
	while (n--)
	{
		*dtmp = *stmp;
		if (*stmp == (unsigned char)c)
			return (++dtmp);
		dtmp++;
		stmp++;
	}
	return (NULL);
}
