/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkimmina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:20:01 by jkimmina          #+#    #+#             */
/*   Updated: 2018/02/24 22:16:23 by jkimmina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	void	*ptr;
	char	*tmp;

	ptr = (void *)malloc(size);
	tmp = (char *)ptr;
	if (!ptr)
		return (NULL);
	while (size--)
		tmp[size] = 0;
	return (ptr);
}
