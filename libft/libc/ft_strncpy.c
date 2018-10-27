/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:58:06 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/26 01:19:33 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*str;
	size_t	i;

	i = -1;
	str = dst;
	while (++i < len)
	{
		if (*src)
			*dst++ = *src++;
		else
			*dst++ = 0;
	}
	return (str);
}
