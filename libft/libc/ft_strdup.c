/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 01:01:06 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/28 14:05:41 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	char	*str;

	str = ft_strnew(ft_strlen(s));
	if (!str)
		return (NULL);
	return (ft_strcpy(str, s));
}
