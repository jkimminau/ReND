/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrsub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:45:45 by jkimmina          #+#    #+#             */
/*   Updated: 2018/05/07 14:06:22 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

wchar_t	*ft_wstrsub(wchar_t const *s, int start, size_t len)
{
	wchar_t	*tmp;
	size_t	i;

	if (!s)
		return (NULL);
	tmp = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < len)
		tmp[i] = s[start + i];
	tmp[i] = '\0';
	return (tmp);
}
