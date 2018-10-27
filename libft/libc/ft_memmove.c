/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:24:05 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/24 21:42:52 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dtmp;
	const char	*stmp;

	dtmp = (char *)dst;
	stmp = (char *)src;
	if (stmp < dtmp)
		while (len--)
			dtmp[len] = stmp[len];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
