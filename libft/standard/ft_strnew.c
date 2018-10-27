/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:34:03 by jkimmina          #+#    #+#             */
/*   Updated: 2018/04/30 18:47:47 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnew(size_t size)
{
	char *tmp;

	tmp = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (size)
		tmp[size--] = 0;
	tmp[size] = '\0';
	return (tmp);
}
