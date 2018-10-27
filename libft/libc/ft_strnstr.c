/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:30:15 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/24 21:45:38 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	if (!*needle || needle == 0)
		return ((char *)haystack);
	while (*haystack && len--)
	{
		i = 0;
		while (haystack[i] == needle[i] && haystack[i])
			i++;
		if (needle[i] == '\0' && len >= i - 1)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
